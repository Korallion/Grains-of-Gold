#include "classes/Player.h"

Player::Player(int x, int y, SDL_Renderer* renderer, std::string path)
{
    pos_x = x;
    pos_y = y;

    vel_x = 0.25;
    vel_y = 0.25;

    texture = new GameTexture();
    texture->loadFromFile( renderer, path);

    width = texture->width;
    height = texture->height;
}

Player::~Player()
{

}

void Player::render( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y, NULL);
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