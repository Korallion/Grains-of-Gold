#pragma once
#include "Entities.h"
#include "Player.h"

void saveEntity(Entity* entity, std::string filePath);
void loadEntity(Entity* entity, std::string filePath);

void savePlayerPosition(Player* player);
void loadPlayerPosition(Player* player);