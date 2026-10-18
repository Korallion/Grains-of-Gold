#pragma once
#include "character.h"

struct Player : Character
{
};

void updatePlayerPosition(Player *player, const Uint8 *keyState, float deltaTime);
