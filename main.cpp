#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "mainLoop.h"
#include "initializeProgram.h"
#include "vertexSpecification.h"
#include "createGraphicsPipeline.h"
#include "cleanUp.h"

// Global Variables
int gScreenWidth = 640, gScreenHeight = 480;
bool gQuit = false;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
GLuint gVertexArrayObject = 0; // VAO
GLuint gVertexBufferObject1 = 0; // VBO
GLuint gVertexBufferObject2 = 0; // VBO
GLuint gGraphicsPipelineShaderProgram = 0;


int main() {
    // 1. Setup the graphics program
    InitializeProgram(&gGraphicsApplicationWindow, gScreenWidth, gScreenHeight, &gOpenGLContext);

    // 2. Setup geometry
    VertexSpecification(gVertexArrayObject,gVertexBufferObject1,gVertexBufferObject2);

    // 3. Create Graphics Pipeline (Its means create at minimum Vertex and Fragment Shaders)
    CreateGraphicsPipeline(gGraphicsPipelineShaderProgram);

    // 4. Call Main Application Loop
    MainLoop(
        &gGraphicsApplicationWindow,
        gScreenWidth, gScreenHeight,
        gQuit,
        gGraphicsPipelineShaderProgram,
        gVertexBufferObject1,
        gVertexBufferObject2,
        gVertexArrayObject);

    // 5. Cleanup data before program finish
    CleanUp(&gGraphicsApplicationWindow);

    return 0;
}



/*
            ********** Version in one single file **********

#include <iostream>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <vector>

const std::string gVertexShaderSource =
    "#version 410 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
    "}\n";

const std::string gFragmentShaderSource =
    "#version 410 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
    "}\n";

void GetOpenGLVersionInfo() {
    std::cout << "Vendor: " <<  glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void VertexSpecification() {
    // This is processing on CPU
    const std::vector<GLfloat> vertexPosition{
        //  X      Y      Z
          -0.8f, -0.8f, 0.0f, // Left Vertex Position
          0.8f, -0.8f, 0.0f,  // Right Vertex Position
          0.0f, 0.8f, 0.0f,   // Top Vertex Position
    };

    // *** Settings on GPU ***

    // Generate and Select VAO
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Start Generating VBO
    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexPosition.size() * sizeof(GLfloat), vertexPosition.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}

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

void CreateGraphicsPipeline() {
    gGraphicsPipelineShaderProgram = CreateShaderProgram(gVertexShaderSource, gFragmentShaderSource);
}


SDL_Window* InitializeProgram() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout<< "SDL3 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    // Create an application window using OpenGL support by SDL
    gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL Series", gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

    if (gGraphicsApplicationWindow == nullptr) {
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
    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    if (gOpenGLContext == nullptr) {
        std::cout<< "SDL_GL_CreateContext could not create the OpenGL context" << std::endl;
        exit(1);
    }

    // Initialize the GLAD Library
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cout << "GLAD was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();

    return gGraphicsApplicationWindow;

}

void Input() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_EVENT_QUIT) {
            std::cout << "Program has finished" << std::endl;
            gQuit = true;
        }
    }
}

// This 2 functions is related to OpenGL

// Responsible to Setting OpenGL State
void PreRender() {
    // Disable depth test and face culling
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Initialize clear color
    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(gGraphicsPipelineShaderProgram);
}

void Render() {
    // Enable the VAO with Attributes configured
    glBindVertexArray(gVertexArrayObject);

    // Select and Enable VBO
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    // Render Data
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Stop using the program
    glUseProgram(0);
}

void MainLoop() {
    while (!gQuit) {
        // Handle inputs
        Input();

        // Setting anything, normally OpenGL State
        PreRender();

        // Draw Calls in OpenGL
        Render();

        // Update Screen (with double buffer system)
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

void CleanUp() {
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}


int main() {
    // 1. Setup the graphics program
    InitializeProgram();

    // 2. Setup geometry
    VertexSpecification();

    // 3. Create Graphics Pipeline (Its means create at minimum Vertex and Fragment Shaders)
    CreateGraphicsPipeline();

    // 4. Call Main Application Loop
    MainLoop();

    // 5. Cleanup data before program finish
    CleanUp();

    return 0;
}
*/
