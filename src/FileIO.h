#pragma once
#include "Entities.h"
#include "Player.h"

void saveEntity(Entity* entity);
void loadEntity(Entity* entity);

void savePlayerPosition(Player* player);
void loadPlayerPosition(Player* player);