#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class GameTexture {
    public:
        GameTexture();
        ~GameTexture();

        bool loadTTF( char* filepath );

        bool loadFromFile( SDL_Renderer* renderer, std::string path );

        bool loadFromText( SDL_Renderer* renderer,std::string text, SDL_Color color);

        void free();

        void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL );

        SDL_Texture* tTexture;
        int width;
        int height;
        TTF_Font* font;
};