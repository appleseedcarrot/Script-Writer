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
        std::map<char,Character> charTextures;

    public:
        Text(std::string& fontFile);
        // ~Text();

        // void renderChar(Shader& s, char c, float x, float y, glm::ivec3 color);
        Character* getChar(char c);

};