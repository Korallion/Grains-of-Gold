#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game_object.h"


struct Character : GameObject {
    float maxSpeed;
    float directionRad;   
    float speed, acceleration;
};

void handleCharacterMovement(Character *character, int deltaTime);
