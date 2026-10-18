#include "player.h"
#include "character.h"

void updatePlayerPosition(Player *player, const Uint8 *keyState, float deltaTime)
{
    int vertical = 0;
    int horizontal = 0;
    float sprint = 1;

    if (keyState[SDL_SCANCODE_LSHIFT])
    {
        sprint = 1.8;
    }

    // find direction of player
    if (keyState[SDL_SCANCODE_D])
    {
        horizontal += 1;
    }

    if (keyState[SDL_SCANCODE_A])
    {
        horizontal -= 1;
    }

    if (keyState[SDL_SCANCODE_S])
    {
        vertical += 1;
    }

    if (keyState[SDL_SCANCODE_W])
    {
        vertical -= 1;
    }

    if (vertical == 0 && horizontal == 0)
    {
        player->speed = 0;
    }
    else
    {
        player->speed = player->maxSpeed;
        player->directionRad = atan2(vertical, horizontal);
    }

    handleCharacterMovement(player, deltaTime);
};

