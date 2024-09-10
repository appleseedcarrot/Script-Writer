// Standard Libraries
#include <map>
#include <string>

// Header File
#include "Character.h"
#include "Shader.h"

// OpenGL Mathematics
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

#pragma once

class Text {

    private:
        // Constructor Functions
        void initFont(std::string& fontFile);

        // Attributes
        std::map<char,Character> charTextures;
        std::string text;
        Shader shader;

        unsigned int VAO, VBO;

    public:
        Text(std::string& fontFile);

        void renderText(float x, float y, float scale, glm::ivec3 color);
        Character* getChar(char c);
        void addChar(char c);
        void delChar();

};