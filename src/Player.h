#pragma once
#include "GameTexture.h"
#include "Entities.h"
#include <string>

typedef struct {
    int x, y;
    int width = 16;
    int height = 32;
    float maxVelocity = 5;
    float direction, currentVelocity;
    GameTexture texture;
} Player;

void renderPlayer(Player* player, SDL_Renderer* renderer , SDL_Rect* cameraRect);

// Point getNewPlayerPosition(Player* player, const Uint8* keyState, float deltaTime);

void updatePlayerPosition(Player* player, const Uint8* keyState, float deltaTime);

bool isPlayerColliding(Player* player, Entity* entity);