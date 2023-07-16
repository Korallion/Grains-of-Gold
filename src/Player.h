#pragma once
#include "GameTexture.h"
#include "Entities.h"
#include <string>

typedef struct {
    int x, y;
    int width = 48;
    int height = 96;
    float maxVelocity = 8;
    float direction, currentVelocity;
    GameTexture texture;
} Player;

enum Collisions {
    NOT_COLLIDING,
    COLLIDING_RIGHT,
    COLLIDING_LEFT,
    COLLIDING_DOWN,
    COLLIDING_UP
};

struct Point {int x, y;};

void renderPlayer(Player* player, SDL_Renderer* renderer , SDL_Rect* cameraRect);

void updatePlayerPosition(Player* player, const Uint8* keyState, float deltaTime);

int isPlayerColliding(Player* player, Point* oldPosition, Entity* entity);
