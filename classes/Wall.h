#pragma once
#include "GameTexture.h"
#include "Rectangle.h"
#include <string>

struct Wall{

        Rectangle rect;

        GameTexture* texture;

        Wall(int x, int y, SDL_Renderer* renderer, std::string path);
        ~Wall();

        void render( SDL_Renderer* renderer );
        
        
};