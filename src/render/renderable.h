#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

struct Renderable : SDL_Rect {
    Texture texture;
};

Renderable createRenderableFromPath(SDL_Renderer *renderer, std::string path, int x, int y);

Renderable createRenderableFromText(SDL_Renderer *renderer, TTF_Font* font, std::string text, SDL_Color color);

void renderTexture(SDL_Renderer *renderer, Renderable* inputTexture, SDL_Rect *sourceRect);

void renderTextureToCamera(SDL_Renderer *renderer, Renderable* inputTexture, SDL_Rect *cameraRect);
