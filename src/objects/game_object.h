#pragma once
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "render/renderable.h"


struct GameObject : Renderable {

    struct Inventory {
        int size;
        std::vector<GameObject> content;
    };
    
    int health, armor;
    Inventory inventory;
    SDL_Rect collisionBox;

    bool blocksMovement;

    // std::function<void(GameObject& self, GameObject& other)> onCollision;
    // std::function<void(GameObject& self, GameObject& other)> onInteract;
    // std::function<void(GameObject& self)> onDeath;
};

bool getIsColliding(GameObject* mover, GameObject* collider);

