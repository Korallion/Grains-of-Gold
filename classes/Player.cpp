#include "Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;
    texture = new GameTexture();
}

Player::~Player()
{

}

void Player::renderPlayer( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y );
}