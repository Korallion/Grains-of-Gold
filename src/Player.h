#pragma once
#include "GameTexture.h"
#include "Entities.h"
#include <string>

// typedef struct {
//     Entity entity;
//     float maxVelocity = 8;
//     float direction, currentVelocity;
// } Player : Mover;

struct Player : Mover
{
};


enum Collisions {
    NOT_COLLIDING,
    COLLIDING_RIGHT,
    COLLIDING_LEFT,
    COLLIDING_DOWN,
    COLLIDING_UP
};

void renderPlayer(Player* player, SDL_Renderer* renderer , SDL_Rect* cameraRect);

void updatePlayerPosition(Player* player, const Uint8* keyState, float deltaTime);

int getCollisionState(Player* player, SDL_Point* oldPosition, Entity* entity);

void applyCollisionState(int collisionState, Player *player, Entity *entity);