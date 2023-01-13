#pragma once
#include "GameTexture.h"
#include <string>

class Player{
    public:
        Player();
        ~Player();

        void renderPlayer( SDL_Renderer* renderer , SDL_Rect* cameraRect);

        void positionUpdate( const Uint8* KeyState , float deltaTime);
        
        float pos_x;
        float pos_y;

        float vel_x;
        float vel_y;

        GameTexture* texture;
};