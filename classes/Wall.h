#pragma once
#include "GameTexture.h"
#include <string>

struct Wall{
        float pos_x;
        float pos_y;

        float width;
        float height;

        GameTexture* texture;

        Wall(int x, int y, SDL_Renderer* renderer, std::string path);
        ~Wall();

        void render( SDL_Renderer* renderer );
        
        
};