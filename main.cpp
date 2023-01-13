#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <sstream>
#include "classes/class_list.h"

const int BACKGROUND_W = 1920;
const int BACKGROUND_W = 1080;

const int SCREEN_W = 1280;
const int SCREEN_H = 720;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Window *gameWindow = NULL;
SDL_Renderer *gameRenderer = NULL;

bool init();
void close();

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL! Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    gameWindow = SDL_CreateWindow("Grains of Gold", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);

    if (gameWindow == NULL)
    {
        printf("Failed to create window! Error: %s\n", SDL_GetError());
        return false;
    }

    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gameRenderer == NULL)
    {
        printf("Failed to create renderer! Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Failed to initialize SDL_iamge! Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    gameWindow = NULL;
    gameRenderer = NULL;
}

int main(int argc, char *args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
        return 0;
    }

    bool quit = false;

    SDL_Event e;

    Player *player = new Player();
    player->texture->loadFromFile(gameRenderer, "sprites/player_sprite.png");
    player->pos_x = (SCREEN_W - player->texture->width) / 2;
    player->pos_y = (SCREEN_H - player->texture->height) / 2;

    GameTexture textRender;
    textRender.loadTTF("ttf/fixed_01.ttf");
    SDL_Color textColor = {0, 0, 0};

    float frameCount = 0;
    float avgFPS;
    int frameStartTime;
    float deltaTime = 0;
    int relativeTime = 0;

    while (!quit)
    {
        frameStartTime = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0XFF);
        SDL_RenderClear(gameRenderer);

        player->positionUpdate(SDL_GetKeyboardState(NULL), deltaTime);
        player->renderPlayer(gameRenderer);

        // Top right corner player data
        textRender.loadFromText(gameRenderer, "X: " + std::to_string(player->pos_x) + "  Y: " + std::to_string(player->pos_y), textColor);
        textRender.render(gameRenderer, 10, 10, NULL, 0.5);

        textRender.loadFromText(gameRenderer, "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s", textColor);
        textRender.render(gameRenderer, 10, 50, NULL, 0.5);

        textRender.loadFromText(gameRenderer, "Frames Rendered: " + std::to_string(frameCount), textColor);
        textRender.render(gameRenderer, 10, 70, NULL, 0.5);

        textRender.loadFromText(gameRenderer, "FPS: " + std::to_string(avgFPS), textColor);
        textRender.render(gameRenderer, 10, 30, NULL, 0.5);

        if (frameStartTime - relativeTime > 200)
        {
            avgFPS = frameCount / (SDL_GetTicks() - relativeTime) * 1000.f;

            frameCount = 0;
            relativeTime += 200;
        }

        SDL_RenderPresent(gameRenderer);

        frameCount++;

        // Calculate and adjust deltaTime for each frame
        deltaTime = SDL_GetTicks() - frameStartTime;

        if (deltaTime < SCREEN_TICKS_PER_FRAME)
        {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - deltaTime);

            deltaTime = SCREEN_TICKS_PER_FRAME;
        }
    }

    return 0;
}