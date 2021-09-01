#pragma once
#include "GameTexture.h"
#include <string>

class Player{
    public:
        Player();
        ~Player();

        void renderPlayer( SDL_Renderer* renderer );

        void velocityUpdate( const Uint8* KeyState );

        void positionUpdate();

        int pos_x;
        int pos_y;

        int vel_x;
        int vel_y;
        int vel_max = 32;

        int accel = 1;
        int decel = 3;

        GameTexture* texture;
};