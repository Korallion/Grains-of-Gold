#include "Entity.h"

void renderEntity(SDL_Renderer *renderer, Entity *entity, int camera_x, int camera_y)
{
    SDL_Rect textureRect = {0, 0, entity->width, entity->height};
    SDL_Rect destinationRect = {entity->x - camera_x, entity->y - camera_y, entity->width, entity->height};

    SDL_RenderCopy(renderer, entity->texture, &textureRect, &destinationRect);
};

void moveEntity(Entity* mover) {
    if (mover->currentVelocity == 0) {
        return;
    }

    mover->x += mover->currentVelocity * cos(mover->direction);
    mover->y += mover->currentVelocity * sin(mover->direction);
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