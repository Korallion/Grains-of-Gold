#include "Player.h"

void renderPlayer(Player *player, SDL_Renderer *renderer, SDL_Rect *cameraRect)
{
    SDL_Rect textureRect = {0, 0, player->texture.width, player->texture.height};
    SDL_Rect destinationRect = {player->x - cameraRect->x, player->y - cameraRect->y, player->width, player->height};

    SDL_RenderCopy(renderer, player->texture.value, &textureRect, &destinationRect);
};

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
        player->currentVelocity = 0;
    }
    else
    {
        player->currentVelocity = player->maxVelocity;
        player->direction = atan2(vertical, horizontal);
    }

    player->x += round(player->currentVelocity * sprint * cos(player->direction));
    player->y += round(player->currentVelocity * sprint * sin(player->direction));
};

int isPlayerColliding(Player *player, Point *oldPosition, Entity *entity)
{
    if (player->x + player->width < entity->x)
    {
        return NOT_COLLIDING;
    }

    if (player->x > entity->x + entity->width)
    {
        return NOT_COLLIDING;
    }

    if (player->y + player->height < entity->y)
    {
        return NOT_COLLIDING;
    }

    if (player->y > entity->y + entity->height)
    {
        return NOT_COLLIDING;
    }

    // Colliding right check
    int distanceRightBefore = entity->x - (oldPosition->x + player->width);
    int distanceRightAfter = entity->x - (player->x + player->width);

    if (distanceRightBefore * distanceRightAfter < 0 || distanceRightBefore == 0)
    {
        return COLLIDING_RIGHT;
    }

    // Colliding left check
    int distanceLeftBefore = entity->x + entity->width - oldPosition->x;
    int distanceLeftAfter = entity->x + entity->width - player->x;

    if (distanceLeftBefore * distanceLeftAfter < 0 || distanceLeftBefore == 0)
    {
        return COLLIDING_LEFT;
    }

    // Colliding down check
    int distanceDownBefore = entity->y - (oldPosition->y + player->height);
    int distanceDownAfter = entity->y - (player->y + player->height);

    if (distanceDownBefore * distanceDownAfter < 0 || distanceDownBefore == 0)
    {
        return COLLIDING_DOWN;
    }

    int distanceUpBefore = entity->y + entity->height - oldPosition->y;
    int distanceUpAfter = entity->y + entity->height - player->y;

    if (distanceUpBefore * distanceUpAfter < 0 || distanceUpBefore == 0)
    {
        return COLLIDING_UP;
    }

    return NOT_COLLIDING;
}