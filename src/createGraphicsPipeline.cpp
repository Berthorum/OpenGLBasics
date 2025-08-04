//
// Created by Ravier de Oliveira on 7/31/2025.
//
#include <iostream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include "createGraphicsPipeline.h"

GLuint CompileShader(GLuint type, const std::string& source) {
    GLuint shaderObject = 0;

    if (type == GL_VERTEX_SHADER) {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src= source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    // Retrieve the result of compilation process
    int result;

    // Retrieve the compilation Status
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;

        // Retrieve the length of info log
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length];

        // Store the info log in errorMessages variable
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages);

        if (type == GL_VERTEX_SHADER) {
            std::cout << "Error compiling vertex shader." << std::endl;
            std::cout << errorMessages << std::endl;
        }else if (type == GL_FRAGMENT_SHADER) {
            std::cout << "Error compiling fragment shader." << std::endl;
            std::cout << errorMessages << std::endl;
        }
        // Deallocating string for log error messages
        delete[] errorMessages;

        glDeleteShader(shaderObject);

        return 0;
    }

    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint programObject = glCreateProgram();

    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Attach shaders into programObject and link it
    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    // Validate program
    glValidateProgram(programObject);

    // Detach the vertex and fragment of program
    glDetachShader(programObject, myVertexShader);
    glDetachShader(programObject, myFragmentShader);

    // Delete the individual shaders
    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);

    return programObject;
}

std::string LoadShaderAsString(const std::string& filename) {
    std::string result;
    std::ifstream myFile(filename.c_str());

    if(myFile.is_open()) {
        std::string line;
        while (std::getline(myFile,  line)) {
            result += line + "\n";
        }
        myFile.close();
    }
    return result;
}

void CreateGraphicsPipeline(GLuint& gGraphicsPipelineShaderProgram) {
    std::string vertexShaderSource = LoadShaderAsString("../shaders/vertexShader.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("../shaders/fragmentShader.glsl");

    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}
