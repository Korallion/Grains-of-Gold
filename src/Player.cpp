#include "Player.h"

void renderPlayer(Player* player, SDL_Renderer* renderer , SDL_Rect* cameraRect)
{
    SDL_Rect textureRect = {0, 0, player->texture.width, player->texture.height};
    SDL_Rect destinationRect = {player->x - cameraRect->x, player->y - cameraRect->y, player->width, player->height};

    SDL_RenderCopy(renderer, player->texture.value, &textureRect, &destinationRect);
};

// Point getNewPlayerPosition(Player* player, const Uint8* keyState, float deltaTime) {
//     int8_t vertical = 0;
//     int8_t horizontal = 0;
//     float sprint = 1;

//     if (keyState[SDL_SCANCODE_LSHIFT]){
//         sprint = 1.8;
//     }

//     // find direction of player
//     if (keyState[SDL_SCANCODE_D]) {
//         horizontal += 1;
//     }

//     if (keyState[SDL_SCANCODE_A]) {
//         horizontal -= 1;
//     }

//     if (keyState[SDL_SCANCODE_S]) {
//         vertical += 1;
//     }

//     if (keyState[SDL_SCANCODE_W]) {
//         vertical -= 1;
//     }

//     if (vertical != 0 || horizontal != 0) {
//         player->direction = atan2(vertical, horizontal);
//     }

//     if (vertical == 0 && horizontal == 0)  {
//         player->currentVelocity = 0;
//     } else {
//         player->currentVelocity = player->maxVelocity;
//     }

//     Point newPosition;

//     newPosition.x = player->x + player->currentVelocity * sprint * cos(player->direction);
//     newPosition.y = player->y + player->currentVelocity * sprint * sin(player->direction);

//     return newPosition;
// }

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

bool isPlayerColliding(Player* player, Entity* entity) {
    if (player->x + player->width < entity->x) {
        return false;
    }

    if (player->x > entity->x + entity->width) {
        return false;
    }
    
    if (player->y + player->height < entity->y) {
        return false;
    }

    if (player->y > entity->y + entity->height) {
        return false;
    }

    return true;
}