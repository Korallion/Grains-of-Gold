#pragma once
#include "Entities.h"
#include "Player.h"

void saveEntityArray(Entity entities[]);
void loadEntityArray(Entity entities[], GameTexture entityTextures[], SDL_Renderer* gameRenderer);

void savePlayerPosition(Player* player);

void loadPlayerPosition(Player* player);