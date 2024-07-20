#include "FileIO.h"

void saveEntityArray(Entity entities[]) {
    const int sizeOfEntity = sizeof(struct Entity);
    const int length = sizeof(&entities) / sizeOfEntity;
    SDL_RWops* file = SDL_RWFromFile( "src/data/entities.bin", "w+b" );

    SDL_RWwrite( file, &entities, sizeOfEntity, length );
    
    SDL_RWclose( file );
};

void loadEntityArray(Entity entities[], GameTexture entityTextures[], SDL_Renderer* gameRenderer) {
    const int sizeOfEntity = sizeof(struct Entity);
    const int length = 8;
    SDL_RWops* file = SDL_RWFromFile("src/data/entities.bin", "r+b");

    for (int i = 4; i < length; i++) {
        SDL_RWread( file, &entities[i], sizeOfEntity, 1);
    };

    SDL_RWclose( file );
}

void savePlayerPosition(Player* player) {
    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "wb" );
    SDL_RWwrite(file, &(player->x), sizeof(player->x), 1);
    SDL_RWwrite(file, &(player->y), sizeof(player->y), 1);
    SDL_RWclose( file );
}

void loadPlayerPosition(Player* player) {
    int x;
    int y;

    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "rb" );
    SDL_RWread(file, &x, sizeof(player->x), 1);
    SDL_RWread(file, &y, sizeof(player->y), 1);
    SDL_RWclose( file );

    player->x = x;
    player->y = y;
}