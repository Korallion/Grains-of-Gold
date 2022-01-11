#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <sstream>
#include "classes/class_list.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

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

    if( TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
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
        player->pos_x = ( SCREEN_W - player->texture->width ) / 2;
        player->pos_y = ( SCREEN_H - player->texture->height ) / 2;

        GameTexture textRender;
        textRender.loadTTF("ttf/fixed_01.ttf");
        SDL_Color textColor = {0,0,0};

        float frameCount = 1;
        float avgFPS;
        int frameStartTime;

        while( !quit )
        {
            frameStartTime = SDL_GetTicks();

            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor( gameRenderer, 0xFF, 0xFF, 0xFF, 0XFF );
            SDL_RenderClear( gameRenderer );

            player->positionUpdate(SDL_GetKeyboardState(NULL));
            player->renderPlayer( gameRenderer );
            
            // Top right corner player data
            textRender.loadFromText( gameRenderer, "X: " + std::to_string(player->pos_x) + "  Y: " + std::to_string(player->pos_y), textColor);
            textRender.render(gameRenderer, 10, 10, NULL, 0.5);

            avgFPS = frameCount / SDL_GetTicks() * 1000.f;
            textRender.loadFromText( gameRenderer, "FPS: " + std::to_string(avgFPS), textColor);
            textRender.render(gameRenderer, 10, 30, NULL, 0.5);

            textRender.loadFromText( gameRenderer, "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s", textColor);
            textRender.render(gameRenderer, 10, 50, NULL, 0.5);

            textRender.loadFromText( gameRenderer, "Frames Rendered: " + std::to_string(frameCount), textColor);
            textRender.render(gameRenderer, 10, 70, NULL, 0.5);

            SDL_RenderPresent( gameRenderer );

            frameCount++;

            if (SDL_GetTicks() - frameStartTime < SCREEN_TICKS_PER_FRAME){
                SDL_Delay( SCREEN_TICKS_PER_FRAME - SDL_GetTicks() + frameStartTime);
            }
        }
    }

    return 0;
}