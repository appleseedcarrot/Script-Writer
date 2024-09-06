// OpenGL Vector
#include <glm/vec2.hpp>

// Freetype2 Library
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma once

class Character {
    private:
        unsigned int textureID;
        char c;
        glm::ivec2 size;
        glm::ivec2 bearing;
        FT_Pos advance;
    public:
        Character(unsigned int textureID, glm::ivec2 size, glm::ivec2 bearing, FT_Pos advance);
        ~Character();
        unsigned int getTextureID();
        FT_Pos getWidth();
        FT_Pos getHeight();
        FT_Pos getBearingX();
        FT_Pos getBearingY();
        FT_Pos getAdvance();

};