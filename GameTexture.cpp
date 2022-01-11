#pragma once
#include "classes/GameTexture.h"
#include <SDL2/SDL_ttf.h>


GameTexture::GameTexture(){
    tTexture = NULL;
    width = 0;
    height = 0;
}

GameTexture::~GameTexture(){
    free();
}

bool GameTexture::loadTTF( char* filepath ){
    bool success = true;

    font = TTF_OpenFont( filepath , 28 );

    if( font == NULL ){
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
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

bool GameTexture::loadFromText( SDL_Renderer* renderer, std::string text, SDL_Color color)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), color);

    if (textSurface == NULL)
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        width = textSurface->w;
        height = textSurface->h;

        tTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    }

}

void GameTexture::free(){

    if( tTexture != NULL ){
        SDL_DestroyTexture( tTexture );
        tTexture = NULL;
        width = 0;
        height = 0;
    }
}

void GameTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){

    SDL_Rect renderRect = { x, y, width, height };

    // If clipping, then change the render rectange to match dimensions of clip
    if( clip != NULL ){
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    SDL_RenderCopy( renderer, tTexture, clip, &renderRect );
}