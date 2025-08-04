//
// Created by Ravier de Oliveira on 7/31/2025.
//
#include <vector>
#include <glad/glad.h>
#include "vertexSpecification.h"

void VertexSpecification(GLuint& gVertexArrayObject, GLuint& gVertexBufferObject1, GLuint& gVertexBufferObject2) {
    // This is processing on CPU
    const std::vector<GLfloat> vertexPosition{
        //  X      Y      Z
        -0.8f, -0.8f, 0.0f, // Left Vertex Position
        0.8f, -0.8f, 0.0f,  // Right Vertex Position
        0.0f, 0.8f, 0.0f,   // Top Vertex Position
    };

    const std::vector<GLfloat> vertexColor{
        //   R      G     B
            0.0f, 0.0f, 1.0f,  // Left Vertex Color
            0.0f, 1.0f, 0.0f,  // Right Vertex Color
            1.0f, 0.0f, 0.0f,  // Top Vertex Color
    };

    // *** Settings on GPU ***

    // Generate and Select VAO
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Start Generating the First VBO For Vertex Position
    glGenBuffers(1, &gVertexBufferObject1);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject1);
    glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW);

    // Create "Layouts" for read data from active VBO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    // --------- Second VBO ----------

    // Defining Vertex Color Attribute
    glGenBuffers(1, &gVertexBufferObject2);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject2);
    glBufferData(GL_ARRAY_BUFFER, vertexColor.size() * sizeof(GLfloat), vertexColor.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

    // Disable the VAO selected and finish attributes creations
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
