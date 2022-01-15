#pragma once
#include "GameTexture.h"
#include "Rectangle.h"
#include <string>

struct Player{
        
        float vel_x;
        float vel_y;

        Rectangle rect;

        GameTexture* texture;
        
        Player(float x, float y, SDL_Renderer* renderer, std::string path);
        ~Player();

        void render( SDL_Renderer* renderer );

        void positionUpdate( const Uint8* KeyState , float deltaTime);
        
        
};