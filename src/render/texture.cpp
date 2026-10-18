#include "texture.h"
#include <SDL2/SDL_ttf.h>

TTF_Font *loadTTF(char *filepath)
{
    TTF_Font *font = TTF_OpenFont(filepath, 28);

    if (font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    return font;
}

Texture loadTextureFromFile(SDL_Renderer *renderer, std::string path)
{
    Texture texture;
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load file image %s! Error: %s\n", path.c_str(), IMG_GetError());
        return texture;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (newTexture == NULL)
    {
        printf("Couldn't make texture from %s! Error: %s\n", path.c_str(), SDL_GetError());
        return texture;
    }

    texture.w = loadedSurface->w;
    texture.h = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_NONE);
    texture.value = newTexture;

    return texture;
}

Texture createTextureFromText(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color color)
{
    Texture texture;
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return texture;
    }

    texture.w = textSurface->w;
    texture.h = textSurface->h;
    texture.value = SDL_CreateTextureFromSurface(renderer, textSurface);

    return texture;
}
