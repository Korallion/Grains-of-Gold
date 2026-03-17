#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <sstream>
#include <iostream>
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

    loadPlayerPosition(&player);
    
    Point oldPlayerPosition;

    GameTexture background = loadTextureFromFile(gameRenderer, "sprites/background_simple.png");
    background.width = BACKGROUND_W;
    background.height = BACKGROUND_H;

    GameTexture text;
    char fontSrc[] = "ttf/fixed_01.ttf";
    TTF_Font *debugFont = loadTTF(fontSrc);
    SDL_Color textColor = {0, 0, 0};

    const std::string genericTextureSrc = "sprites/red.png";
    const GameTexture genericTexture = loadTextureFromFile(gameRenderer, genericTextureSrc);
    std::vector<Entity*> collisionEntities;

    Entity walls[4];
    int wallsIndex = 4;
    Entity redBlock;

    for (int i = 0; i < 4; i++) {
        collisionEntities.push_back(&walls[i]);
    }

    loadEntityArray(walls, 4, "simple_border", gameRenderer, genericTextureSrc);
    loadEntity(&redBlock, "red_block");
    redBlock.texture = genericTexture;


    const int CAMERA_W = 1280;
    const int CAMERA_H = 720;
    int cameraPositionX;
    int cameraPositionY;
    SDL_Rect cameraRect;

    float frameCount = 0;
    float avgFPS;
    int frameStartTime;
    float deltaTime = 0;
    int relativeTime = 0;

    std::string playerCoordinates;
    std::string fpsDisplay;
    std::string timePassed;
    std::string playerDirection;
    std::string playerSpeed;

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

        oldPlayerPosition.x = player.x;
        oldPlayerPosition.y = player.y;

        updatePlayerPosition(&player, SDL_GetKeyboardState(NULL), deltaTime);

        for (int i = 0; i < collisionEntities.size(); i++)
        {
            int collisionState = getCollisionState(&player, &oldPlayerPosition, collisionEntities[i]);
            applyCollisionState(collisionState, &player, collisionEntities[i]);
        }

        cameraPositionX = player.x - (CAMERA_W - player.width) / 2;
        cameraPositionY = player.y - (CAMERA_H - player.height) / 2;
        cameraRect = {cameraPositionX, cameraPositionY, CAMERA_W, CAMERA_H};
        renderTextureToCamera(gameRenderer, &background, 0, 0, &cameraRect);

        for (int i = 0; i < wallsIndex; i++)
        {
            renderEntity(&walls[i], gameRenderer, &cameraRect);
        }

        renderEntity(&redBlock, gameRenderer, &cameraRect);

        renderPlayer(&player, gameRenderer, &cameraRect);

        // Top right corner game data
        playerCoordinates = "X: " + std::to_string(player.x) + "  Y: " + std::to_string(player.y);
        fpsDisplay = "FPS: " + std::to_string(avgFPS);
        timePassed = "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s";
        playerDirection = "Player direction: " + std::to_string(player.direction);
        playerSpeed = "Player speed x: " + std::to_string(player.x - oldPlayerPosition.x) + "\nPlayer speed y: " + std::to_string(player.y - oldPlayerPosition.y);

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

    savePlayerPosition(&player);
    saveEntity(&redBlock, "red_block");
    saveEntityArray(walls, 4, "simple_border");
    grains::close(gameWindow, gameRenderer);

    return 0;
}
