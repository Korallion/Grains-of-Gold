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

SDL_Rect screenGeometry = {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720};

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDL_Window *gameWindow;
SDL_Renderer *gameRenderer;

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
    player.x = (BACKGROUND_W - player.width) / 2;
    player.y = (BACKGROUND_H - player.height) / 2;
    player.direction = 0;

    GameTexture background = loadTextureFromFile(gameRenderer, "sprites/simple_background.png");
    background.width = BACKGROUND_W;
    background.height = BACKGROUND_H;

    GameTexture text;
    TTF_Font *debugFont = loadTTF("ttf/fixed_01.ttf");
    SDL_Color textColor = {0, 0, 0};

    Entity barriers[12];
    barriers[0].texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    barriers[0].x = 0;
    barriers[0].y = -10;
    barriers[0].width = 1920;
    barriers[0].height = 10;

    barriers[1].texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    barriers[1].x = 0;
    barriers[1].y = 1080;
    barriers[1].width = 1920;
    barriers[1].height = 10;

    barriers[2].texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    barriers[2].x = -10;
    barriers[2].y = 0;
    barriers[2].width = 10;
    barriers[2].height = 1080;

    barriers[3].texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    barriers[3].x = 1920;
    barriers[3].y = 0;
    barriers[3].width = 10;
    barriers[3].height = 1080;

    int barriersIndex = 4;

    const int CAMERA_W = 1280;
    const int CAMERA_H = 720;
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

        Point oldPlayerPosition;
        oldPlayerPosition.x = player.x;
        oldPlayerPosition.y = player.y;

        updatePlayerPosition(&player, SDL_GetKeyboardState(NULL), deltaTime);

        for (int i = 0; i < barriersIndex; i++)
        {
            int collisionState = getCollisionState(&player, &oldPlayerPosition, &barriers[i]);
            applyCollisionState(collisionState, &player, &barriers[i]);
        }

        cameraPositionX = player.x - (CAMERA_W - player.width) / 2;
        cameraPositionY = player.y - (CAMERA_H - player.height) / 2;

        SDL_Rect cameraRect = {cameraPositionX, cameraPositionY, CAMERA_W, CAMERA_H};
        renderTextureToCamera(gameRenderer, &background, 0, 0, &cameraRect);

        for (int i = 0; i < barriersIndex; i++)
        {
            renderEntity(&barriers[i], gameRenderer, &cameraRect);
        }

        renderPlayer(&player, gameRenderer, &cameraRect);

        // Top right corner game data
        std::string playerCoordinates = "X: " + std::to_string(player.x) + "  Y: " + std::to_string(player.y);
        std::string fpsDisplay = "FPS: " + std::to_string(avgFPS);
        std::string timePassed = "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s";
        std::string playerDirection = "Player direction: " + std::to_string(player.direction);
        std::string playerSpeed = "Player speed x: " + std::to_string(player.x - oldPlayerPosition.x) + "\nPlayer speed y: " + std::to_string(player.y - oldPlayerPosition.y);

        text = createTextureFromText(gameRenderer, debugFont, playerCoordinates, textColor);
        renderTexture(gameRenderer, &text, 10, 10, NULL);

        text = createTextureFromText(gameRenderer, debugFont, fpsDisplay, textColor);
        renderTexture(gameRenderer, &text, 10, 40, NULL);

        text = createTextureFromText(gameRenderer, debugFont, timePassed, textColor);
        renderTexture(gameRenderer, &text, 10, 70, NULL);

        text = createTextureFromText(gameRenderer, debugFont, playerDirection, textColor);
        renderTexture(gameRenderer, &text, 10, 100, NULL);

        text = createTextureFromText(gameRenderer, debugFont, playerSpeed, textColor);
        renderTexture(gameRenderer, &text, 10, 130, NULL);

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