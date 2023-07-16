#include "GameTexture.h"
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

GameTexture loadTextureFromFile(SDL_Renderer *renderer, std::string path)
{
    GameTexture texture;
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

    texture.width = loadedSurface->w;
    texture.height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_NONE);
    texture.value = newTexture;

    return texture;
}

GameTexture createTextureFromText(SDL_Renderer *renderer, TTF_Font *font, std::string text, SDL_Color color)
{
    GameTexture texture;
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return texture;
    }

    texture.width = textSurface->w;
    texture.height = textSurface->h;
    texture.value = SDL_CreateTextureFromSurface(renderer, textSurface);

    return texture;
}

void renderTexture(SDL_Renderer *renderer, GameTexture *inputTexture, int x, int y, SDL_Rect *sourceRect)
{
    SDL_Rect destinationRect = {x, y, inputTexture->width, inputTexture->height};

    // If clipping, then change the render rectange to match dimensions of clip
    if (sourceRect != NULL)
    {
        destinationRect.w = sourceRect->w;
        destinationRect.h = sourceRect->h;
    }

    SDL_RenderCopy(renderer, inputTexture->value, sourceRect, &destinationRect);
}

void renderTextureToCamera(SDL_Renderer *renderer, GameTexture *inputTexture, int x, int y, SDL_Rect *cameraRect)
{
    SDL_Rect textureRect = {0, 0, inputTexture->width, inputTexture->height};
    SDL_Rect destinationRect = {x - cameraRect->x, y - cameraRect->y, inputTexture->width, inputTexture->height};

    SDL_RenderCopy(renderer, inputTexture->value, &textureRect, &destinationRect);
}