#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameTexture {
    public:
        GameTexture();
        ~GameTexture();
        bool loadFromFile( SDL_Renderer* renderer, std::string path );
        void free();
        void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip );

        SDL_Texture* tTexture;
        int width;
        int height;
};