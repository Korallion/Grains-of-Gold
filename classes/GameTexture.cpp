#include "./GameTexture.h"

GameTexture::GameTexture(){
    tTexture = NULL;
    width = 0;
    height = 0;
}

GameTexture::~GameTexture(){
    free();
}

bool GameTexture::loadFromFile( SDL_Renderer* renderer, std::string path ){
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL ){

        printf( "Unable to load file image %s! Error: %s\n", path.c_str(), IMG_GetError() );

    } else {

        newTexture = SDL_CreateTextureFromSurface( renderer,  loadedSurface);

        if( newTexture == NULL ){

            printf( "Couldn't make texture from %s! Error: %s\n", path.c_str(), SDL_GetError() );

        } else {

            width = loadedSurface->w;
            height = loadedSurface->h;

        }

        SDL_FreeSurface( loadedSurface );
    }

    tTexture = newTexture;
    return tTexture != NULL;
}

void GameTexture::free(){

    if( tTexture != NULL ){
        SDL_DestroyTexture( tTexture );
        tTexture = NULL;
        width = 0;
        height = 0;
    }
}

void GameTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip ){

    SDL_Rect renderRect = { x, y, width, height };

    if( clip != NULL ){
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopy( renderer, tTexture, clip, &renderRect );
}