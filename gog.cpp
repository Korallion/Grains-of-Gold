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
        int moveSpeed;

        bool collision;
};