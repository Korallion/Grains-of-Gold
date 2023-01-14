#include "Player.h"

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

void Player::renderPlayer( SDL_Renderer* renderer , SDL_Rect* cameraRect)
{
    texture->renderToCamera( renderer, pos_x, pos_y, cameraRect);
}

void Player::positionUpdate( const Uint8* keyState, float deltaTime)
{
    float sprint = 1;
    float diagonal = 1;

    if (keyState[SDL_SCANCODE_LSHIFT]){
        sprint = 1.8;
    }
    
    // Fun check to see if player is moving diagonally, if so, we slow them down
    if (((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D]) && keyState[SDL_SCANCODE_W]) || ((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D]) && keyState[SDL_SCANCODE_S])){
        diagonal = 1/ 1.4;
    }

    //Check x direction
    if (keyState[SDL_SCANCODE_A])
    {
        pos_x -= vel_x * sprint * diagonal * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        pos_x += vel_x * sprint * diagonal * deltaTime;
    }

    // Y direction next
    if ( keyState[SDL_SCANCODE_S])
    {
        pos_y += vel_y * sprint * diagonal * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        pos_y -= vel_y * sprint * diagonal * deltaTime;
    }    
}