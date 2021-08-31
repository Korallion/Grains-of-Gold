#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include "./classes/GameTexture.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;

class Room {
    public:
        Room();
        ~Room();

    private:
        GameTexture* texture;
        int width;
        int height;
};

class Entity {
    public:
        Entity();
        ~Entity();

        GameTexture* texture;
        int width;
        int height;
        std::string name;

        int x_pos;
        int y_pos;

        bool collision;
};

// BRAINSTORM::
// What are the categories of entities in this game?
// There are living, moving creatures: animals, people, the player, enemies
// There are living plants that change state and can be harvested
// There are natural resources that can be broken for items
// There are walls that don't move and can't break
// There are portals (doors) that change the room
// There are items that can drop from killed / destroyed things
// There is farmland / soil, that can be tilled or fertilized and planted on

class Player: public Entity {
    public:
        Player();
        ~Player();
};

class Plant: public Entity {
    public:
        Plant();
        ~Plant();
    
    private:
        int maxGrowthTime;
        int growSpeed;

};

// class ResourceEntity {

// };

// class Wall {

// };

// class Portal {

// };

// class Item {

// };

// class GroundPatch {

// };

SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;



int main( int argc, char* args[] ){



}