#include "classes/Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;

    vel_x = 1;
    vel_y = 1;

    texture = new GameTexture();
}

Player::~Player()
{

}

void Player::renderPlayer( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y );
}

void Player::positionUpdate( const Uint8* keyState )
{
    // Update position
    // X direction first
    // Check if only one of the x_directional keys is pressed
    if (keyState[SDL_SCANCODE_A])
    {
        pos_x -= vel_x;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        pos_x += vel_x;
    }

    // Y direction next
    if ( keyState[SDL_SCANCODE_S])
    {
        pos_y += vel_y;
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        pos_y -= vel_y;
    }

    
}