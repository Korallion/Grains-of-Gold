#include "character.h"
#include <cmath>

void handleCharacterMovement(Character* character, int deltaTime) {
    if (character->speed == 0) {
        return;
    }

    character->x += round(character->speed * std::cos(character->directionRad) * deltaTime / 1000);
    character->y += round(character->speed * std::sin(character->directionRad) * deltaTime / 1000);
}
