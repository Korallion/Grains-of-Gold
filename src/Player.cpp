#include "Player.h"

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

    player->entity.collision_box.x += round(player->currentVelocity * sprint * cos(player->direction));
    player->entity.collision_box.y += round(player->currentVelocity * sprint * sin(player->direction));
};

int getCollisionState(Player *player, SDL_Point *oldPosition, Entity *entity)
{
    if (!SDL_HasIntersection(&player->entity.collision_box, &entity->collision_box)) {
        return NOT_COLLIDING;
    }

    // Colliding right check
    int distanceRightBefore = entity->collision_box.x - (oldPosition->x + player->entity.collision_box.w);
    int distanceRightAfter = entity->collision_box.x - (player->entity.collision_box.x + player->entity.collision_box.w);

    if (distanceRightBefore * distanceRightAfter < 0 || distanceRightBefore == 0)
    {
        player->entity.collision_box.x = entity->collision_box.x - player->entity.collision_box.w;
        return COLLIDING_RIGHT;
    }

    // Colliding left check
    int distanceLeftBefore = entity->collision_box.x + entity->collision_box.w - oldPosition->x;
    int distanceLeftAfter = entity->collision_box.x + entity->collision_box.w - player->entity.collision_box.x;

    if (distanceLeftBefore * distanceLeftAfter < 0 || distanceLeftBefore == 0)
    {
        player->entity.collision_box.x = entity->collision_box.x + entity->collision_box.w;
        return COLLIDING_LEFT;
    }

    // Colliding down check
    int distanceDownBefore = entity->collision_box.y - (oldPosition->y + player->entity.collision_box.h);
    int distanceDownAfter = entity->collision_box.y - (player->entity.collision_box.y + player->entity.collision_box.h);

    if (distanceDownBefore * distanceDownAfter < 0 || distanceDownBefore == 0)
    {
        player->entity.collision_box.y = entity->collision_box.y - player->entity.collision_box.h;
        return COLLIDING_DOWN;
    }

    // Colliding up check
    int distanceUpBefore = entity->collision_box.y + entity->collision_box.h - oldPosition->y;
    int distanceUpAfter = entity->collision_box.y + entity->collision_box.h - player->entity.collision_box.y;

    if (distanceUpBefore * distanceUpAfter < 0 || distanceUpBefore == 0)
    {
        player->entity.collision_box.y = entity->collision_box.y + entity->collision_box.h;
        return COLLIDING_UP;
    }

    return NOT_COLLIDING;
}

void applyCollisionState(int collisionState, Player *player, Entity *entity) {
    switch(collisionState) {
        case NOT_COLLIDING:
            break;
        case COLLIDING_RIGHT:
            player->entity.collision_box.x = entity->collision_box.x - player->entity.collision_box.w;
            break;
        case COLLIDING_LEFT:
            player->entity.collision_box.x = entity->collision_box.x + entity->collision_box.w;
            break;
        case COLLIDING_UP:
            player->entity.collision_box.y = entity->collision_box.y + entity->collision_box.h;
            break;
        case COLLIDING_DOWN:
            player->entity.collision_box.y = entity->collision_box.y - player->entity.collision_box.h;
            break;
    }
}