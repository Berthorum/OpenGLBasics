//
// Created by Ravier de Oliveira on 7/31/2025.
//

#include <iostream>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "mainLoop.h"

void Input(bool& gQuit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_EVENT_QUIT) {
            std::cout << std::endl << "**** Program has been finished ****" << std::endl;
            gQuit = true;
        }
    }
}

// This 2 functions is related to OpenGL

// Responsible to Setting OpenGL State
void PreRender(const int& gScreenWidth, const int& gScreenHeight, const GLuint& gGraphicsPipelineShaderProgram) {
    // Disable depth test and face culling
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize clear color
    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(gGraphicsPipelineShaderProgram);
}

void Render( const GLuint& gVertexArrayObject, const GLuint& gVertexBufferObject1, const GLuint& gVertexBufferObject2 ) {
    // Enable the VAO with Attributes configured
    glBindVertexArray(gVertexArrayObject);

    // Select and Enable VBO
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject1);

    // Render Data
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Stop using the program
    glUseProgram(0);
}

void MainLoop(SDL_Window** gGraphicsApplicationWindow, const int& gScreenWidth, const int& gScreenHeight,
        bool& gQuit, const GLuint& gGraphicsPipelineShaderProgram, const GLuint& gVertexBufferObject1,
        const GLuint& gVertexBufferObject2, const GLuint& gVertexArrayObject) {

    while (!gQuit) {
        // Handle inputs
        Input(gQuit);

        // Setting anything, normally OpenGL State
        PreRender(gScreenWidth, gScreenHeight, gGraphicsPipelineShaderProgram);

        // Draw Calls in OpenGL
        Render(gVertexBufferObject1, gVertexBufferObject2, gVertexArrayObject);

        // Update Screen (with double buffer system)
        SDL_GL_SwapWindow(*gGraphicsApplicationWindow);
    }
}