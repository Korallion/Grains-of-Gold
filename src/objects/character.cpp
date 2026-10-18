#include "character.h"
#include <cmath>

void handleCharacterMovement(Character* character, int deltaTime) {
    if (character->speed == 0) {
        return;
    }

    character->x += round(character->speed * std::cos(character->directionRad) * deltaTime / 1000);
    character->y += round(character->speed * std::sin(character->directionRad) * deltaTime / 1000);
    character->collisionBox.x = character->x;
    character->collisionBox.y = character->y;
}

int getCollisionState(Character *character, GameObject *collider)
{
    if (!SDL_HasIntersection(&character->collisionBox, &collider->collisionBox)) {
        return NOT_COLLIDING;
    }

    // Colliding right check
    int distanceRightBefore = collider->collisionBox.x - (character->oldPosition.x + character->collisionBox.w);
    int distanceRightAfter = collider->collisionBox.x - (character->collisionBox.x + character->collisionBox.w);

    if (distanceRightBefore * distanceRightAfter < 0 || distanceRightBefore == 0)
    {
        character->collisionBox.x = collider->collisionBox.x - character->collisionBox.w;
        return COLLIDING_RIGHT;
    }

    // Colliding left check
    int distanceLeftBefore = collider->collisionBox.x + collider->collisionBox.w - character->oldPosition.x;
    int distanceLeftAfter = collider->collisionBox.x + collider->collisionBox.w - character->collisionBox.x;

    if (distanceLeftBefore * distanceLeftAfter < 0 || distanceLeftBefore == 0)
    {
        character->collisionBox.x = collider->collisionBox.x + collider->collisionBox.w;
        return COLLIDING_LEFT;
    }

    // Colliding down check
    int distanceDownBefore = collider->collisionBox.y - (character->oldPosition.y + character->collisionBox.h);
    int distanceDownAfter = collider->collisionBox.y - (character->collisionBox.y + character->collisionBox.h);

    if (distanceDownBefore * distanceDownAfter < 0 || distanceDownBefore == 0)
    {
        character->collisionBox.y = collider->collisionBox.y - character->collisionBox.h;
        return COLLIDING_DOWN;
    }

    // Colliding up check
    int distanceUpBefore = collider->collisionBox.y + collider->collisionBox.h - character->oldPosition.y;
    int distanceUpAfter = collider->collisionBox.y + collider->collisionBox.h - character->collisionBox.y;

    if (distanceUpBefore * distanceUpAfter < 0 || distanceUpBefore == 0)
    {
        character->collisionBox.y = collider->collisionBox.y + collider->collisionBox.h;
        return COLLIDING_UP;
    }

    return NOT_COLLIDING;
}

void applyCollisionState(int collisionState, Character *character, GameObject *collider) {
    switch(collisionState) {
        case NOT_COLLIDING:
            break;
        case COLLIDING_RIGHT:
            character->collisionBox.x = collider->collisionBox.x - character->collisionBox.w;
            character->x = character->collisionBox.x;
            break;
        case COLLIDING_LEFT:
            character->collisionBox.x = collider->collisionBox.x + collider->collisionBox.w;
            character->x = character->collisionBox.x;
            break;
        case COLLIDING_UP:
            character->collisionBox.y = collider->collisionBox.y + collider->collisionBox.h;
            character->y = character->collisionBox.y;
            break;
        case COLLIDING_DOWN:
            character->collisionBox.y = collider->collisionBox.y - character->collisionBox.h;
            character->y = character->collisionBox.y;
            break;
    }
}

void handleCollision(Character* character, GameObject* collider) {
    int collisionState = getCollisionState(character, collider);
    applyCollisionState(collisionState, character, collider);
}
