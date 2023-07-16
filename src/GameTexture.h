#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct GameTexture{
    SDL_Texture* value;
    int width, height;
};

TTF_Font* loadTTF(char *filepath);

GameTexture loadTextureFromFile(SDL_Renderer *renderer, std::string path);

GameTexture createTextureFromText(SDL_Renderer *renderer, TTF_Font* font, std::string text, SDL_Color color);

void renderTexture(SDL_Renderer *renderer, GameTexture* inputTexture, int x, int y, SDL_Rect *sourceRect);

void renderTextureToCamera(SDL_Renderer *renderer, GameTexture* inputTexture, int x, int y, SDL_Rect *cameraRect);