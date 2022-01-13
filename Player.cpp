#include "classes/Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;

    vel_x = 0.25;
    vel_y = 0.25;

    texture = new GameTexture();
}

Player::~Player()
{

}

void Player::renderPlayer( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y, NULL, 1 );
}

void Player::positionUpdate( const Uint8* keyState, float deltaTime)
{
    // Check if sprinting
    float sprint = 1;

    if (keyState[SDL_SCANCODE_LSHIFT]){
        sprint = 1.8;
    }

    //Check x direction
    if (keyState[SDL_SCANCODE_A])
    {
        pos_x -= vel_x * sprint * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        pos_x += vel_x * sprint * deltaTime;
    }

    // Y direction next
    if ( keyState[SDL_SCANCODE_S])
    {
        pos_y += vel_y * sprint * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        pos_y -= vel_y * sprint * deltaTime;
    }

    
}