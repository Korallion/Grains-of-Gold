#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>

const int SCREEN_W = 640;
const int SCREEN_H = 480;

class GameTexture {
    public:
        GameTexture();
        ~GameTexture();
        bool loadFromFile( std::string path );
        void free();
        void render( int x, int y );

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* tTexture;
        int width;
        int height;

};

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

    private:
        GameTexture* texture;
        int width;
        int height;

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

class Character {

};

class Plant {

};

class ResourceEntity {

};

class Wall {

};

class Portal {

};

class Item {

};

class GroundPatch {

};