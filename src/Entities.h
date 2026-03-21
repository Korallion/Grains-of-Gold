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
    SDL_Rect collision_box;
    GameTexture texture;
};

struct Mover : Entity
{
    float maxVelocity = 8;
    float direction, velocity;
};

void renderEntity(Entity *entity, SDL_Renderer *renderer, SDL_Rect* cameraRect);

void moveEntity(Mover* mover);

bool checkRectCollision(SDL_Rect* rectA, SDL_Rect* rectB);


// void handleRectangularCollision(Entity *moverEntity, Entity *stationaryEntity);