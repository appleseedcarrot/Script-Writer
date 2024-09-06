// Header File
#include "Character.h"
#include <iostream>

#include <glad/glad.h>

Character::Character(unsigned int textureID, glm::ivec2 size, glm::ivec2 bearing, FT_Pos advance) {
    this->textureID = textureID;
    this->size = size;
    this->bearing = bearing;
    this->advance = advance;
}

Character::~Character() {
//     glDeleteTextures(1, &this->textureID);
//     std::cout << "Texture Deleted" << std::endl;
}

unsigned int Character::getTextureID() {
    return (this->textureID);
}

FT_Pos Character::getWidth() {
    return this->size.x;
}

FT_Pos Character::getHeight() {
    return this->size.y;
}

FT_Pos Character::getBearingX() {
    return this->bearing.x;
}

FT_Pos Character::getBearingY() {
    return this->bearing.y;
}

FT_Pos Character::getAdvance() {
    return this->advance;
}