#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Initialize.h"

namespace grains
{
    bool init(SDL_Window **gameWindow, SDL_Renderer **gameRenderer, int screenWidth, int screenHeight);

    void close(SDL_Window *gameWindow, SDL_Renderer *gameRenderer);
}