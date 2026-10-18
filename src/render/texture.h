#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct Texture{
    SDL_Texture* value;
    int w, h;
};

TTF_Font* loadTTF(char *filepath);

Texture loadTextureFromFile(SDL_Renderer *renderer, std::string path);

Texture createTextureFromText(SDL_Renderer *renderer, TTF_Font* font, std::string text, SDL_Color color);
