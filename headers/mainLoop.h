//
// Created by Ravier de Oliveira on 7/31/2025.
//

#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <SDL3/SDL.h>
#include <glad/glad.h>

void MainLoop(SDL_Window** gGraphicsApplicationWindow, const int& gScreenWidth, const int& gScreenHeight,
        bool& gQuit, const GLuint& gGraphicsPipelineShaderProgram,  const GLuint& gVertexBufferObject1, const GLuint& gVertexBufferObject2,
        const GLuint& gVertexArrayObject);

#endif //MAINLOOP_H


