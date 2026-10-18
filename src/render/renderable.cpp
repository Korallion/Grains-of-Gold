#include "renderable.h"
#include <SDL2/SDL_ttf.h>

Renderable createRenderableFromPath(SDL_Renderer *renderer, std::string path, int x, int y) {
    Renderable renderable;
    renderable.x = x;
    renderable.y = y;

    renderable.texture = loadTextureFromFile(renderer, path);

    renderable.w = renderable.texture.w;
    renderable.h = renderable.texture.h;    

    return renderable;
}

Renderable createRenderableFromTexture(SDL_Renderer *renderer, Texture* texture, int x, int y) {
    Renderable renderable;
    renderable.x = x;
    renderable.y = y;

    renderable.texture = *texture;

    renderable.w = renderable.texture.w;
    renderable.h = renderable.texture.h;    

    return renderable;
}

Renderable createRenderableFromText(SDL_Renderer *renderer, int x, int y, TTF_Font* font, std::string text, SDL_Color color) {
    Renderable renderable;
    renderable.x = x;
    renderable.y = y;

    renderable.texture = createTextureFromText(renderer, font, text, color);

    renderable.w = renderable.texture.w;
    renderable.h = renderable.texture.h;    

    return renderable;
}

void renderTexture(SDL_Renderer *renderer, Renderable *renderable, SDL_Rect *sourceRect)
{
    SDL_Rect destinationRect = {renderable->x, renderable->y, renderable->w, renderable->h};

    // If clipping, then change the render rectangle to match dimensions of clip
    if (sourceRect != NULL)
    {
        destinationRect.w = sourceRect->w;
        destinationRect.h = sourceRect->h;
    }

    SDL_RenderCopy(renderer, renderable->texture.value, sourceRect, &destinationRect);
}

void renderTextureToCamera(SDL_Renderer *renderer, Renderable *renderable, SDL_Rect *cameraRect)
{
    int x = renderable->x;
    int y = renderable->y;
    // SDL_Rect textureRect = {0, 0, renderable->texture.w, renderable->texture.h};
    SDL_Rect destinationRect = {x - cameraRect->x, y - cameraRect->y, renderable->w, renderable->h};

    SDL_RenderCopy(renderer, renderable->texture.value, NULL, &destinationRect);
}
