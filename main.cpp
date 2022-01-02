#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include "classes/class_list.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;

SDL_Window* gameWindow = NULL;
SDL_Renderer* gameRenderer = NULL;

bool init();
void close();

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Failed to initialize SDL! Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        gameWindow = SDL_CreateWindow( "Grains of Gold", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN );

        if( gameWindow == NULL )
        {
            printf( "Failed to create window! Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gameRenderer = SDL_CreateRenderer( gameWindow, -1, SDL_RENDERER_ACCELERATED );

            if( gameRenderer == NULL )
            {
                printf( "Failed to create renderer! Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;

                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "Failed to initialize SDL_iamge! Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

void close()
{
    SDL_DestroyRenderer( gameRenderer );
    SDL_DestroyWindow( gameWindow );
    gameWindow = NULL;
    gameRenderer = NULL;
}

int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        bool quit = false;

        SDL_Event e;

        Player* player = new Player();

        player->texture->loadFromFile( gameRenderer, "sprites/player_sprite.png" );

        player->pos_x = ( SCREEN_W - player->texture->width ) / 3;
        player->pos_y = ( SCREEN_H - player->texture->height ) / 3;

        while( !quit )
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            player->positionUpdate(SDL_GetKeyboardState(NULL));

            SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0XFF );
            SDL_RenderClear( gameRenderer );

            player->renderPlayer( gameRenderer );

            SDL_RenderPresent( gameRenderer );
        }
    }

    return 0;
}