#include "Entities.h"

void renderEntity(Entity *entity, SDL_Renderer *renderer, SDL_Rect* cameraRect)
{
    SDL_Rect textureRect = {0, 0, entity->texture.width, entity->texture.height};
    SDL_Rect destinationRect = {entity->x - cameraRect->x, entity->y - cameraRect->y, entity->width, entity->height};

    SDL_RenderCopy(renderer, entity->texture.value, &textureRect, &destinationRect);
};

void moveEntity(Mover* mover) {
    if (mover->currentVelocity == 0) {
        return;
    }

    mover->entity->x += mover->currentVelocity * cos(mover->direction);
    mover->entity->y += mover->currentVelocity * sin(mover->direction);
}

// bool isCollidingRectangular(Entity *moverEntity, Entity *stationaryEntity)
// {
//     if (moverEntity->x + moverEntity->width <= stationaryEntity->x || stationaryEntity->x + stationaryEntity->width <= moverEntity->x)
//     {
//         return 0;
//     }

//     if (moverEntity->y + moverEntity->height <= stationaryEntity->y || stationaryEntity->y + stationaryEntity->height <= moverEntity->y)
//     {
//         return 0;
//     }

//     return true;
// };

// void handleRectangularCollision(Entity *moverEntity, Entity *stationaryEntity) {
//     bool isColliding = isCollidingRectangular(moverEntity, stationaryEntity);

//     if (isColliding) {
//         if ()
//     }
// }