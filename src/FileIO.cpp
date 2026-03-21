#include "FileIO.h"

void saveEntity(Entity* entity, std::string filePath) {
    std::string savePath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile(savePath.c_str(), "wb" );

    SDL_RWwrite( file, &entity->collision_box.x, sizeof(entity->collision_box.x), 1 );
    SDL_RWwrite( file, &entity->collision_box.y, sizeof(entity->collision_box.y), 1 );
    SDL_RWwrite( file, &entity->collision_box.w, sizeof(entity->collision_box.w), 1 );
    SDL_RWwrite( file, &entity->collision_box.h, sizeof(entity->collision_box.h), 1 );

    SDL_RWclose( file );
};

void loadEntity(Entity* entity, std::string filePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    SDL_RWread( file, &entity->collision_box.x, sizeof(entity->collision_box.x), 1 );
    SDL_RWread( file, &entity->collision_box.y, sizeof(entity->collision_box.y), 1 );
    SDL_RWread( file, &entity->collision_box.w, sizeof(entity->collision_box.w), 1 );
    SDL_RWread( file, &entity->collision_box.h, sizeof(entity->collision_box.h), 1 );

    SDL_RWclose( file );
};

void saveEntityArray(Entity entityArray[], int arrayLength, std::string filePath) {
    std::string savePath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile(savePath.c_str(), "wb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWwrite( file, &entityArray[i].collision_box.x, sizeof( entityArray[i].collision_box.x), 1 );
        SDL_RWwrite( file, &entityArray[i].collision_box.y, sizeof( entityArray[i].collision_box.y), 1 );
        SDL_RWwrite( file, &entityArray[i].collision_box.w, sizeof( entityArray[i].collision_box.w), 1 );
        SDL_RWwrite( file, &entityArray[i].collision_box.h, sizeof( entityArray[i].collision_box.h), 1 );
    }

    SDL_RWclose( file );
};

void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWread( file, &entityArray[i].collision_box.x, sizeof( entityArray[i].collision_box.x), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.y, sizeof( entityArray[i].collision_box.y), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.w, sizeof( entityArray[i].collision_box.w), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.h, sizeof( entityArray[i].collision_box.h), 1 );
    }

    SDL_RWclose( file );
};

void loadEntityArray(Entity entityArray[], int arrayLength, std::string filePath, SDL_Renderer *renderer, std::string texturePath) {
    std::string loadPath = "src/data/" + filePath + ".bin";
    SDL_RWops* file = SDL_RWFromFile( loadPath.c_str(), "rb" );

    for (int i = 0; i < arrayLength; i++) {
        SDL_RWread( file, &entityArray[i].collision_box.x, sizeof( entityArray[i].collision_box.x), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.y, sizeof( entityArray[i].collision_box.y), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.w, sizeof( entityArray[i].collision_box.w), 1 );
        SDL_RWread( file, &entityArray[i].collision_box.h, sizeof( entityArray[i].collision_box.h), 1 );
        entityArray[i].texture = loadTextureFromFile(renderer, texturePath);
    }

    SDL_RWclose( file );
};

void savePlayerPosition(Player* player) {
    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "wb" );
    SDL_RWwrite(file, &(player->collision_box.x), sizeof(player->collision_box.x), 1);
    SDL_RWwrite(file, &(player->collision_box.y), sizeof(player->collision_box.y), 1);
    SDL_RWclose( file );
}

void loadPlayerPosition(Player* player) {
    SDL_RWops* file = SDL_RWFromFile( "src/data/player_position.bin", "rb" );
    SDL_RWread(file, &(player->collision_box.x), sizeof(player->collision_box.x), 1);
    SDL_RWread(file, &(player->collision_box.y), sizeof(player->collision_box.y), 1);
    SDL_RWclose( file );
}