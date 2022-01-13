#pragma once
#include "GameTexture.h"
#include <string>

class Player{
    public:
        float pos_x;
        float pos_y;

        float vel_x;
        float vel_y;

        float width;
        float height;

        GameTexture* texture;
        
        Player(int x, int y, SDL_Renderer* renderer, std::string path);
        ~Player();

        void render( SDL_Renderer* renderer );

        void positionUpdate( const Uint8* KeyState , float deltaTime);
        
        
};