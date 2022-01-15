#include "classes/Wall.h"

Wall::Wall(int x, int y, SDL_Renderer* renderer, std::string path){
    rect.x = x;
    rect.y = y;

    texture = new GameTexture();
    texture->loadFromFile( renderer, path);

    rect.w = texture->width;
    rect.h = texture->height;
}

Wall::~Wall(){

}

void Wall::render( SDL_Renderer* renderer )
{
    texture->render( renderer, NULL, rect.x, rect.y);
}