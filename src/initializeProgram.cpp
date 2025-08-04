//
// Created by Ravier de Oliveira on 7/31/2025.
//
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "initializeProgram.h"

void GetOpenGLVersionInfo() {
    std::cout << "Vendor: " <<  glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitializeProgram(SDL_Window** gGraphicsApplicationWindow, const int& gScreenWidth, const int& gScreenHeight,  SDL_GLContext* gOpenGLContext ) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout<< "SDL3 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    // Create an application window using OpenGL support by SDL
    *gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL Basics", gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

    if (*gGraphicsApplicationWindow == nullptr) {
        std::cout<< "SDL_Window could not create the window" << std::endl;
        exit(1);
    }

    //              **** Setting OpenGL Context properties ****

    // NOTE: macOS would not work because don't support versions above OpenGL 4.1.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Forcing use Modern OpenGL features ridding off legacy functions and others elements
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Activating double buffering system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Defining how many bits the depth buffer will have
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create an OpenGL Graphics Context
    *gOpenGLContext = SDL_GL_CreateContext(*gGraphicsApplicationWindow);

    if (*gOpenGLContext == nullptr) {
        std::cout<< "SDL_GL_CreateContext could not create the OpenGL context" << std::endl;
        exit(1);
    }

    // Initialize the GLAD Library
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cout << "GLAD was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();

}