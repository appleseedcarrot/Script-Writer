// OpenGL Function Pointers
#include <glad/glad.h>

// Standard Libraries
#include <iostream>

// Header File
#include "Shader.h"

// Function Definitions
Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {

    // Create Shader program
    unsigned int program = glCreateProgram();

    // Creates OpenGL vertex and fragment shaders
    unsigned int vertShader = createShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragShader = createShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Compile vertex and fragment shaders into final shader program
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    int isLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (!isLinked) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length);
        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "GL ERROR: Program linking failed! " << message << std::endl;
        glDeleteProgram(program);
    }

    // Check that shader is working properly
    glValidateProgram(program);

    // Free vertex and fragment shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    shaderProgram = program;
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

unsigned int Shader::createShader(unsigned int type, const std::string& source) {

    // Create the shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Check that the shader was compiled properly
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char)*length);
        glGetShaderInfoLog(id, 512, &length, message);
        std::cout << "GL ERROR: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader could not be compiled! " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::getProgramID() {
    return this->shaderProgram;
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}