#include "FileIO.h"

void saveEntity(Entity* entity, std::string filePath) {
    std::string savePath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile(savePath.c_str(), "wb" );

    SDL_RWwrite( file, &entity->x, sizeof( entity->x), 1 );
    SDL_RWwrite( file, &entity->y, sizeof( entity->y), 1 );
    SDL_RWwrite( file, &entity->width, sizeof( entity->width), 1 );
    SDL_RWwrite( file, &entity->height, sizeof( entity->height), 1 );

    SDL_RWclose( file );
};

void loadEntity(Entity* entity, std::string filePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    SDL_RWread( file, &entity->x, sizeof( entity->x), 1 );
    SDL_RWread( file, &entity->y, sizeof( entity->y), 1 );
    SDL_RWread( file, &entity->width, sizeof( entity->width), 1 );
    SDL_RWread( file, &entity->height, sizeof( entity->height), 1 );

    SDL_RWclose( file );
};

void saveEntityArray(Entity entityArray[], int arrayLength, std::string filePath) {
    std::string savePath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile(savePath.c_str(), "wb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWwrite( file, &entityArray[i].x, sizeof( entityArray[i].x), 1 );
        SDL_RWwrite( file, &entityArray[i].y, sizeof( entityArray[i].y), 1 );
        SDL_RWwrite( file, &entityArray[i].width, sizeof( entityArray[i].width), 1 );
        SDL_RWwrite( file, &entityArray[i].height, sizeof( entityArray[i].height), 1 );
    }

    SDL_RWclose( file );
};

void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWread( file, &entityArray[i].x, sizeof( entityArray[i].x), 1 );
        SDL_RWread( file, &entityArray[i].y, sizeof( entityArray[i].y), 1 );
        SDL_RWread( file, &entityArray[i].width, sizeof( entityArray[i].width), 1 );
        SDL_RWread( file, &entityArray[i].height, sizeof( entityArray[i].height), 1 );
    }

    SDL_RWclose( file );
};

void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath, SDL_Renderer *renderer, std::string texturePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWread( file, &entityArray[i].x, sizeof( entityArray[i].x), 1 );
        SDL_RWread( file, &entityArray[i].y, sizeof( entityArray[i].y), 1 );
        SDL_RWread( file, &entityArray[i].width, sizeof( entityArray[i].width), 1 );
        SDL_RWread( file, &entityArray[i].height, sizeof( entityArray[i].height), 1 );
        entityArray[i].texture = loadTextureFromFile(renderer, texturePath);
    }

    SDL_RWclose( file );
};

void savePlayerPosition(Player* player) {
    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "wb" );
    SDL_RWwrite(file, &(player->x), sizeof(player->x), 1);
    SDL_RWwrite(file, &(player->y), sizeof(player->y), 1);
    SDL_RWclose( file );
}

void loadPlayerPosition(Player* player) {
    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "rb" );
    SDL_RWread(file, &(player->x), sizeof(player->x), 1);
    SDL_RWread(file, &(player->y), sizeof(player->y), 1);
    SDL_RWclose( file );
}