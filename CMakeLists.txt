cmake_minimum_required(VERSION 3.31)
project(OpenGLBasics)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
include(FetchContent)

set(SDL3_VERSION 3.2.18)

function(include_sdl3 libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY  ${gitURL}
        GIT_TAG  ${gitTag}
        GIT_SHALLOW     TRUE
        GIT_PROGRESS    TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()
find_package(SDL3 QUIET)

if(NOT SDL3_FOUND)
    include_sdl3(SDL3 https://github.com/libsdl-org/SDL.git release-${SDL3_VERSION})
endif()

# Project

# For execution in one single file
#set(SOURCE_FILES main.cpp glad/src/glad.c)

#target_include_directories(${PROJECT_NAME} PUBLIC ${SDL3_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad/include/)

set(SOURCE_FILES main.cpp
        glad/src/glad.c
        src/initializeProgram.cpp
        src/vertexSpecification.cpp
        src/createGraphicsPipeline.cpp
        src/mainLoop.cpp
        src/cleanUp.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL3_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/glad/include/ ${PROJECT_SOURCE_DIR}/headers)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

