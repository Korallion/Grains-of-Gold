#pragma once
#include "GameTexture.h"
#include <string>

class Player{
    public:
        Player();
        ~Player();

        void renderPlayer( SDL_Renderer* renderer );

        void movementUpdate();

        int pos_x;
        int pos_y;

        int vel_x;
        int vel_y;
        int vel_max = 8;

        int a = 1;
        int decceleration = 3;

        GameTexture* texture;
};