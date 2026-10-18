#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game_object.h"


struct Character : GameObject {
    float maxSpeed;
    float directionRad;   
    float speed;
    SDL_Point oldPosition;
};

enum CollisionState {
    NOT_COLLIDING,
    COLLIDING_UP,
    COLLIDING_DOWN,
    COLLIDING_LEFT,
    COLLIDING_RIGHT
};

void handleCharacterMovement(Character *character, int deltaTime);

int getCollisionState(Character *character, GameObject* gameObject);

void handleCollision(Character *character, GameObject* gameObject);
