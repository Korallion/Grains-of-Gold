#include "classes/Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;

    vel_x = 0;
    vel_y = 0;

    texture = new GameTexture();
}

Player::~Player()
{

}

void Player::renderPlayer( SDL_Renderer* renderer )
{
    texture->render( renderer, pos_x, pos_y );
}

void Player::velocityUpdate( const Uint8* keyState )
{
    int newXVelocity = vel_x;
    int newYVelocity = vel_y;

    // Velocity change
    // X direction first
    // Check if only one of the x_directional keys is pressed
    if (keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D])
    {
        // If player is going in opposite direction to keypress, include natural deceleration
        if ( vel_x > 0 )
        {
            newXVelocity -= accel + decel;
        }
        else
        {
            newXVelocity -= accel;
        }
    }
    else if (!keyState[SDL_SCANCODE_A] && keyState[SDL_SCANCODE_D])
    {
        if ( vel_x < 0 )
        {
            newXVelocity += accel + decel;
        }
        else
        {
            newXVelocity += accel;
        }
    }
    // What if nothing is pressed or both keys are pressed?
    // Then we simply decellerate, and set the velocity to zero so we don't accelerate in the other direction
    else
    {
        if ( vel_x < 0 )
        {
            newXVelocity = std::min( vel_x + decel, 0 );
        }
        else
        {
            newXVelocity = std::max( vel_x - decel, 0 );
        }
    }

    // Y direction next
    if (!keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_S])
    {
        if ( vel_y < 0 ){
            newYVelocity += accel + decel;
        }
        else
        {
            newYVelocity += accel;
        }
    }
    else if (keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S])
    {
        if ( vel_y > 0 ){
            newYVelocity -= accel + decel;
        }
        else
        {
            newYVelocity -= accel;
        }
    }
    else
    {
        if ( vel_y < 0 )
        {
            newYVelocity = std::min( vel_x + decel, 0 );
        }
        else
        {
            newYVelocity = std::max( vel_x - decel, 0 );
        }
    }

    // Make sure the velocities don't exceed the maximum
    if ( newXVelocity > vel_max )
    {
        newXVelocity = vel_max;
    }
    else if ( newXVelocity < -vel_max )
    {
        newXVelocity = -vel_max;
    }

    if ( newYVelocity > vel_max )
    {
        newYVelocity = vel_max;
    }
    else if ( newYVelocity < -vel_max )
    {
        newYVelocity = -vel_max;
    }

    vel_x = newXVelocity;
    vel_y = newYVelocity;
}

void Player::positionUpdate()
{
    pos_x += vel_x;
    pos_y += vel_y;
}