//
// Created by Ravier de Oliveira on 7/31/2025.
//

#include <SDL3/SDL.h>
#include "cleanUp.h"

void CleanUp(SDL_Window** gGraphicsApplicationWindow) {
    SDL_DestroyWindow(*gGraphicsApplicationWindow);
    SDL_Quit();
}
