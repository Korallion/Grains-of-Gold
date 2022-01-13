#include "classes/Wall.h"

Wall::Wall(int x, int y, SDL_Renderer* renderer, std::string path){
    pos_x = x;
    pos_y = y;

    texture = new GameTexture();
    texture->loadFromFile( renderer, path);

    width = texture->width;
    height = texture->height;
}

Wall::~Wall(){

}

void Wall::render( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y, NULL);
}