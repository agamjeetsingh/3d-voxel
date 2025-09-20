//
// Created by Agamjeet Singh on 20/09/25.
//

#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H
#include <iostream>

#include "glad/glad.h"

inline const char* vertexShaderSource = R"(
#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
uniform mat4 MVP;  // combined Model-View-Projection matrix

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0); // directly output clip-space position
    TexCoords = aTexCoords;
}
)";

inline const char* fragmentShaderSource = R"(
#version 410 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, TexCoords);
}
)";

class TextureShader {
public:
    TextureShader() {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Check for compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
        }

        // Link shaders into shader program
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader Program Linking Failed:\n" << infoLog << std::endl;
        }

        // After linking, shaders can be deleted
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        this->shaderProgram = shaderProgram;
    }

    [[nodiscard]] unsigned int getShaderProgram() const {
        if (!glIsProgram(shaderProgram)) {
            throw std::runtime_error("Tried to access shader program after it has been destroyed.");
        }
        return shaderProgram;
    }

    ~TextureShader() {
        if (glIsProgram(shaderProgram))
            glDeleteProgram(shaderProgram);
    }

    TextureShader(const TextureShader&) = delete;
    TextureShader& operator=(const TextureShader&) = delete;

    TextureShader(TextureShader&& other) noexcept {
        shaderProgram = other.shaderProgram;
        other.shaderProgram = 0;
    }

    TextureShader& operator=(TextureShader&& other) noexcept {
        if (this != &other) {
            if (glIsProgram(shaderProgram))
                glDeleteProgram(shaderProgram);
            shaderProgram = other.shaderProgram;
            other.shaderProgram = 0;
        }
        return *this;
    }

private:
    unsigned int shaderProgram;
};



#endif //TEXTURESHADER_H
