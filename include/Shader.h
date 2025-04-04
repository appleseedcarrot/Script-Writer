// Standard Libraries
#include <string>

#pragma once

class Shader {
    private:
        // Shader ID
        unsigned int shaderProgram;

        // Functions
        unsigned int createShader(unsigned int type, const std::string& source);

    public:
        // Constructor, Destructor
        Shader(const std::string& vertexShader, const std::string& fragmentShader);
        ~Shader();

        // Getters
        unsigned int getProgramID();

        // Use and Activate the Shader
        void use();

        // Set Shader Uniforms
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
};