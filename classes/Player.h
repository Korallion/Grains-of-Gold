#pragma once
#include "GameTexture.h"
#include <string>

class Player{
    public:
        Player();
        ~Player();

        void renderPlayer( SDL_Renderer* renderer );

        void positionUpdate( const Uint8* KeyState );
        
        int pos_x;
        int pos_y;

        int vel_x = 8;
        int vel_y = 8;

        GameTexture* texture;
};