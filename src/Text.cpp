// Freetype2 Library
#include <ft2build.h>
#include FT_FREETYPE_H

// OpenGL Function Pointers
#include <glad/glad.h>

// Standard Libraries
#include <iostream>
#include <utility>

// Header File
#include "Text.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string vertShader =
"#version 410 core\n"
"layout (location = 0) in vec4 vertex;\n"
"out vec2 TexCoords;\n"
"\n"
"uniform mat4 projection;"
"\n"
"void main()\n"
"{\n"
"   gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
"   TexCoords = vertex.zw;"
"}\n";
                                    
std::string fragShader = 
"#version 410 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;"
"\n"
"uniform sampler2D text;"
"uniform vec3 textColor;"
"\n"
"void main()\n"
"{\n"
"   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);"
"   color = vec4(textColor, 1.0) * sampled;\n"
"}\n";

Text::Text(std::string& fontFile) : text(""), shader(vertShader, fragShader) { 

    // Convert TTF file into usable textures
    initFont(fontFile);
    

    // Create Buffers
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

    // Configure shader properties
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1920), 0.0f, static_cast<float>(1080));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
}

void Text::initFont(std::string& fontFile) {

    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, fontFile.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 32; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use

            Character character = Character(
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            );

            charTextures.emplace(c, std::move(character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Character* Text::getChar(char c) {
    auto it = this->charTextures.find(c);
    return &it->second;
}

void Text::addChar(char c) {
    this->text.push_back(c);
}

void Text::delChar() {
    if (this->text.size() == 0) {
        return;
    }
    else 
        this->text.pop_back();
}

void Text::renderText(float x, float y, float scale, glm::ivec3 color) {
    // Activate the Shader
    this->shader.use();

    // Set Shading Color
    glUniform3f(glGetUniformLocation(this->shader.getProgramID(),"textColor"), color.x, color.y, color.z);

    // Set Configuration for Render
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = this->text.begin(); c != this->text.end(); c++) 
    {
        Character* ch = this->getChar(*c);
        
        float xpos = x + ch->getBearingX() * scale;
        float ypos = y - (ch->getHeight() - ch->getBearingY()) * scale;

        float w = ch->getWidth() * scale;
        float h = ch->getHeight() * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch->getTextureID());
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->getAdvance() >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}