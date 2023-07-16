#pragma once
#include <string>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct Entity
{
    int x, y, width, height;
    float direction, currentVelocity, maxVelocity;

    SDL_Texture* texture;
};

void renderEntity(SDL_Renderer* renderer, Entity* entity, int camera_x, int camera_y);

void moveEntity(Entity* mover);

// void handleRectangularCollision(Entity *moverEntity, Entity *stationaryEntity);