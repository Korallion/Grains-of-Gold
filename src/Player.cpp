#include "Player.h"

void renderPlayer(Player* player, SDL_Renderer* renderer , SDL_Rect* cameraRect)
{
    SDL_Rect textureRect = {0, 0, player->texture.width, player->texture.height};
    SDL_Rect destinationRect = {player->x - cameraRect->x, player->y - cameraRect->y, player->width, player->height};

    SDL_RenderCopy(renderer, player->texture.value, &textureRect, &destinationRect);
};

void updatePlayerPosition(Player* player, const Uint8* keyState, float deltaTime)
{
    int8_t vertical = 0;
    int8_t horizontal = 0;
    float sprint = 1;

    if (keyState[SDL_SCANCODE_LSHIFT]){
        sprint = 1.8;
    }

    // find direction of player
    if (keyState[SDL_SCANCODE_D]) {
        horizontal += 1;
    }

    if (keyState[SDL_SCANCODE_A]) {
        horizontal -= 1;
    }

    if (keyState[SDL_SCANCODE_S]) {
        vertical += 1;
    }

    if (keyState[SDL_SCANCODE_W]) {
        vertical -= 1;
    }

    if (vertical != 0 || horizontal != 0) {
        player->direction = atan2(vertical, horizontal);
    }

    if (vertical == 0 && horizontal == 0)  {
        player->currentVelocity = 0;
    } else {
        player->currentVelocity = player->maxVelocity;
    }

    player->x += player->currentVelocity * sprint * cos(player->direction);
    player->y += player->currentVelocity * sprint * sin(player->direction);
}