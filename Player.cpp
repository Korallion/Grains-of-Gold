#include "classes/Player.h"

Player::Player(float x, float y, SDL_Renderer* renderer, std::string path)
{
    rect.x = x;
    rect.y = y;

    vel_x = 0.25;
    vel_y = 0.25;

    texture = new GameTexture();
    texture->loadFromFile( renderer, path);

    rect.w = texture->width;
    rect.h = texture->height;
}

Player::~Player()
{
    texture->free();
}

void Player::render( SDL_Renderer* renderer )
{
    texture->render( renderer, NULL, rect.x, rect.y);
}

void Player::positionUpdate( const Uint8* keyState, float deltaTime)
{
    // Check if sprinting
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
        rect.x -= vel_x * sprint * diagonal * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        rect.x += vel_x * sprint * diagonal * deltaTime;
    }

    // Y direction next
    if ( keyState[SDL_SCANCODE_S])
    {
        rect.y += vel_y * sprint * diagonal * deltaTime;
    }
    else if (keyState[SDL_SCANCODE_W])
    {
        rect.y -= vel_y * sprint * diagonal * deltaTime;
    }    
}