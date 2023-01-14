#include "Initialize.h"

namespace grains
{
    bool init(SDL_Window **gameWindow, SDL_Renderer **gameRenderer, int screenWidth, int screenHeight)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("Failed to initialize SDL! Error: %s\n", SDL_GetError());
            return false;
        }

        !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            printf("Failed to initialize SDL_image! Error: %s\n", IMG_GetError());
            return false;
        }

        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }

        *gameWindow = SDL_CreateWindow("Grains of Gold", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        if (*gameWindow == NULL)
        {
            printf("Failed to create window! Error: %s\n", SDL_GetError());
            return false;
        }

        *gameRenderer = SDL_CreateRenderer(*gameWindow, -1, SDL_RENDERER_ACCELERATED);

        if (*gameRenderer == NULL)
        {
            printf("Failed to create renderer! Error: %s\n", SDL_GetError());
            return false;
        }

        return true;
    }

    void close(SDL_Window *gameWindow, SDL_Renderer *gameRenderer)
    {
        SDL_DestroyRenderer(gameRenderer);
        SDL_DestroyWindow(gameWindow);
    }
}