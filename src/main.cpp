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
    player.collision_box.w = player.texture.width;
    player.collision_box.h = player.texture.height;
    player.collision_box.x = (BACKGROUND_W - player.collision_box.w) / 2;
    player.collision_box.y = (BACKGROUND_H - player.collision_box.h) / 2;
    player.direction = 0;
    
    loadPlayerPosition(&player);
    
    SDL_Point oldPlayerPosition;

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

    walls[0].collision_box.x = 0;
    walls[0].collision_box.y = 0;
    walls[0].collision_box.w = 10;
    walls[0].collision_box.h = BACKGROUND_H;

    walls[1].collision_box.x = BACKGROUND_W;
    walls[1].collision_box.y = 0;
    walls[1].collision_box.w = 10;
    walls[1].collision_box.h = BACKGROUND_H;

    walls[2].collision_box.x = 0;
    walls[2].collision_box.y = 0;
    walls[2].collision_box.w = BACKGROUND_W;
    walls[2].collision_box.h = 10;

    walls[3].collision_box.x = 0;
    walls[3].collision_box.y = BACKGROUND_H;
    walls[3].collision_box.w = BACKGROUND_W;
    walls[3].collision_box.h = 10;

    for (int i = 0; i < 4; i++) {
        walls[i].texture = genericTexture;
        collisionEntities.push_back(&walls[i]);
    }

    // loadEntityArray(walls, 4, "simple_border", gameRenderer, genericTextureSrc);
    // loadEntity(&redBlock, "red_block");
    redBlock.texture = genericTexture;

    const int CAMERA_W = 1280;
    const int CAMERA_H = 720;
    SDL_Rect cameraRect = {0, 0, CAMERA_W, CAMERA_H};

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

        oldPlayerPosition.x = player.collision_box.x;
        oldPlayerPosition.y = player.collision_box.y;

        updatePlayerPosition(&player, SDL_GetKeyboardState(NULL), deltaTime);

        for (int i = 0; i < collisionEntities.size(); i++)
        {
            int collisionState = getCollisionState(&player, &oldPlayerPosition, collisionEntities[i]);
            applyCollisionState(collisionState, &player, collisionEntities[i]);
        }

        cameraRect.x = player.collision_box.x - (CAMERA_W - player.collision_box.w) / 2, 
        cameraRect.y = player.collision_box.y - (CAMERA_H - player.collision_box.h) / 2, 
        renderTextureToCamera(gameRenderer, &background, 0, 0, &cameraRect);

        for (int i = 0; i < wallsIndex; i++)
        {
            renderEntity(&walls[i], gameRenderer, &cameraRect);
        }

        renderEntity(&redBlock, gameRenderer, &cameraRect);
        renderEntity(&player, gameRenderer, &cameraRect);

        // Top right corner game data
        playerCoordinates = "X: " + std::to_string(player.collision_box.x) + "  Y: " + std::to_string(player.collision_box.y);
        fpsDisplay = "FPS: " + std::to_string(avgFPS);
        timePassed = "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s";
        playerDirection = "Player direction: " + std::to_string(player.direction);
        playerSpeed = "Player speed x: " + std::to_string(player.collision_box.x - oldPlayerPosition.x) + "\nPlayer speed y: " + std::to_string(player.collision_box.y - oldPlayerPosition.y);

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
    // saveEntity(&redBlock, "red_block");
    // saveEntityArray(walls, 4, "simple_border");
    grains::close(gameWindow, gameRenderer);

    return 0;
}
