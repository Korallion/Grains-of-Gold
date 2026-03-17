#pragma once
#include "Entities.h"
#include "Player.h"
#include "GameTexture.h"

void saveEntity(Entity* entity, std::string filePath);
void loadEntity(Entity* entity, std::string filePath);

void saveEntityArray(Entity entityArray[], int arrayLength, std::string filePath);
void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath);
void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath, SDL_Renderer *renderer, std::string texturePath);

void savePlayerPosition(Player* player);
void loadPlayerPosition(Player* player);