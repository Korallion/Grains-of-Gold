#pragma once
#include <string>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameTexture.h"

struct Entity
{
    int x, y, width, height;
    GameTexture texture;
};

struct Mover
{
    Entity* entity;
    float direction, currentVelocity, maxVelocity;
};

void renderEntity(Entity *entity, SDL_Renderer *renderer, SDL_Rect* cameraRect);

void moveEntity(Mover* mover);

// void handleRectangularCollision(Entity *moverEntity, Entity *stationaryEntity);