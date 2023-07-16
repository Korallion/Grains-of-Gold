#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <sstream>
#include "include_list.h"

const int BACKGROUND_W = 1920;
const int BACKGROUND_H = 1080;

const int CAMERA_W = 1280;
const int CAMERA_H = 720;

SDL_Rect screenGeometry = { SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Window* gameWindow;
SDL_Renderer* gameRenderer;

int main(int argc, char *args[])
{
    if (!grains::init(&gameWindow, &gameRenderer, screenGeometry.w, screenGeometry.h))
    {
        printf("Failed to initialize!\n");
        return 0;
    }

    bool quit = false;

    SDL_Event e;

    Player player;
    player.texture = loadTextureFromFile(gameRenderer, "sprites/player_sprite.png");
    player.x = (BACKGROUND_W - player.width)/ 2;
    player.y = (BACKGROUND_H - player.height) / 2;
    player.direction = 0;
    player.maxVelocity = 2;

    GameTexture background = loadTextureFromFile(gameRenderer, "sprites/simple_background.png");
    background.width = BACKGROUND_W;
    background.height = BACKGROUND_H;

    GameTexture text;
    TTF_Font* debugFont = loadTTF("ttf/fixed_01.ttf");
    SDL_Color textColor = {0, 0, 0};

    Entity barrier;
    barrier.texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    barrier.x = 0;
    barrier.y = 0;
    barrier.width = 100;
    barrier.height = 300;

    Entity wall;
    wall.texture = loadTextureFromFile(gameRenderer, "sprites/green.png");
    wall.x = 1200;
    wall.y = 300;
    wall.width = 400;
    wall.height = 800;

    int cameraPositionX;
    int cameraPositionY;

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

        updatePlayerPosition(&player, SDL_GetKeyboardState(NULL), deltaTime);
        cameraPositionX = player.x - (CAMERA_W - player.width) / 2;
        cameraPositionY = player.y - (CAMERA_H - player.height) / 2;

        SDL_Rect cameraRect = {cameraPositionX, cameraPositionY, CAMERA_W, CAMERA_H};

        renderTextureToCamera(gameRenderer, &background, 0, 0, &cameraRect);
        renderEntity(&barrier, gameRenderer, &cameraRect);
        renderEntity(&wall, gameRenderer, &cameraRect);

        renderPlayer(&player, gameRenderer, &cameraRect);

        // Top right corner game data
        std::string playerCoordinates = "X: " + std::to_string(player.x) + "  Y: " + std::to_string(player.y);
        std::string fpsDisplay = "FPS: " + std::to_string(avgFPS);
        std::string timePassed = "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s";
        std::string framesRendered = "Frames Rendered: " + std::to_string(frameCount);

        text = createTextureFromText(gameRenderer, debugFont, playerCoordinates, textColor);
        renderTexture(gameRenderer, &text, 10, 10, NULL);

        text = createTextureFromText(gameRenderer, debugFont, fpsDisplay, textColor);
        renderTexture(gameRenderer, &text, 10, 40, NULL);

        text = createTextureFromText(gameRenderer, debugFont, timePassed, textColor);
        renderTexture(gameRenderer, &text, 10, 70, NULL);

        text = createTextureFromText(gameRenderer, debugFont, framesRendered, textColor);
        renderTexture(gameRenderer, &text, 10, 100, NULL);

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

    grains::close(gameWindow, gameRenderer);

    return 0;
}