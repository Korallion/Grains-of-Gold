#include "classes/Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;

    vel_x = 3;
    vel_y = 3;

    texture = new GameTexture();
}

Player::~Player()
{

}

void Player::renderPlayer( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y, NULL, 1 );
}

void Player::positionUpdate( const Uint8* keyState )
{
    // Check if sprinting
    int sprint = 1;

    if (keyState[SDL_SCANCODE_LSHIFT]){
        sprint = 2;
    }

    //Check x direction
    if (keyState[SDL_SCANCODE_A])
    {
        pos_x -= vel_x * sprint;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        pos_x += vel_x * sprint;
    }

    // Y direction next
    if ( keyState[SDL_SCANCODE_S])
    {
        pos_y += vel_y * sprint;
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        pos_y -= vel_y * sprint;
    }

    
}