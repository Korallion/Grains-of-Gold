#include "Entities.h"

void renderEntity(Entity *entity, SDL_Renderer *renderer, SDL_Rect* cameraRect)
{
    SDL_Rect textureRect = {0, 0, entity->texture.width, entity->texture.height};
    SDL_Rect destinationRect = getRenderRect(entity, cameraRect);

    SDL_RenderCopy(renderer, entity->texture.value, &textureRect, &destinationRect);
};

void moveEntity(Mover* mover) {
    if (mover->velocity == 0) {
        return;
    }

    mover->collision_box.x += mover->velocity * cos(mover->direction);
    mover->collision_box.y += mover->velocity * sin(mover->direction);
}

SDL_Rect getRenderRect(Entity* entity, SDL_Rect* cameraRect) {
    SDL_Rect renderRect;
    int widthDiff = entity->collision_box.w - entity->texture.width;
    int heightDiff = entity->collision_box.h - entity->texture.height;

    renderRect.x = entity->collision_box.x - cameraRect->x - widthDiff / 2;
    renderRect.y = entity->collision_box.y - cameraRect->y - heightDiff / 2;
    renderRect.w = entity->texture.width;
    renderRect.h = entity->texture.height;

    return renderRect;
}

bool checkRectCollision(SDL_Rect* rectA, SDL_Rect* rectB) {
    if (rectA->x + rectA->w < rectB->x)
    {
        return false;
    }

    if (rectA->x > rectB->x + rectB->w)
    {
        return false;
    }

    if (rectA->y + rectA->h < rectB->y)
    {
        return false;
    }

    if (rectA->y > rectB->y + rectB->h)
    {
        return false;
    }

    return true;
}