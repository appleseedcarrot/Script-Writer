// OpenGL Function Pointers
#include <glad/glad.h>

// SDL Library and OpenGL
#include "SDL.h"

// For TTF Font Loading
#include "ft2build.h"
#include FT_FREETYPE_H

// OpenGL Mathematics Library
#include <glm/vec2.hpp>

// Standard Libraries
#include <iostream>
#include <map>
#include <utility>

    //****************************************** Structs *************************************************//
    //****************************************************************************************************//
struct Char {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    FT_Pos advance;
};

int main() {

    //****************************************** Initialize SDL ******************************************//
    //****************************************************************************************************//
    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        std::cout << "SDL ERROR: SDL could not be initialized. SDL error " << SDL_GetError() << std::endl;
        return -1;
    }
    std::cout << "SDL Initialized\n";

    // Load OpenGL
    SDL_GL_LoadLibrary(NULL);
    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    std::cout << "OpenGL Loaded by SDL\n";

    // Create Window
    SDL_Window* window = SDL_CreateWindow("Text Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "SDL ERROR: Window could not be created. SDL error " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
    std::cout << "SDL Window Created\n";

    // Create OpenGL Context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    std::cout << "GL Context Created\n";

    // Initialize Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "SDL ERROR: Renderer could not be created. SDL error " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    std::cout << "SDL Renderer Created\n";

    // Check OpenGL properties
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "GLAD ERROR: Could not load OpenGL Function Pointers. SDL Error " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    std::cout << "OpenGL loaded\n";
    //std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    //std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    //std::cout << "Version: " << glGetString(GL_VERSION) << "\n";

    //****************************************** Load TrueType Font ***************************************//
    //*****************************************************************************************************//

    // Initialize FreeType Library
    FT_Library library;
    FT_Face face;

    if (FT_Init_FreeType(&library))
    {
        std::cout << "FREETYPE ERROR: FreeType could not be initialized. Closing Program..." << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load Font into Face
    FT_New_Face(library,"assets/fonts/cour.ttf",0,&face);
    if (FT_New_Face(library,"assets/fonts/cour.ttf",0,&face)) {
        std::cout << "FREETYPE ERROR: Invalid format or Failure to Load Font. Closing Program..." << std::endl;
        FT_Done_FreeType(library);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Set Pixel Font Size
    FT_Set_Pixel_Sizes(face, 0, 40);

    // Initialize Font Texture Map
    std::map<char, Char> charMap;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load each character onto charMap
    for (unsigned char c = 0; c < 128; c++) {

        // Load Character onto Face
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "FREETYPE ERROR: Failed to load Glyph. Closing Program..." << std::endl;  
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
        Char character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        charMap.insert(std::pair<char, Char>(c, character));

    }

    // Free Freetype Resources
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    // Quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // End Program
    return 0;
}