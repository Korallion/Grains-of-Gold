#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdio>
#include <cmath>
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
    
    std::vector<GameObject*> collisionEntities;
    std::vector<Renderable*> renderEntities;

    Player player;
    player.texture = loadTextureFromFile(gameRenderer, "sprites/player_sprite.png");
    player.w = player.texture.w;
    player.h = player.texture.h;
    player.x = (BACKGROUND_W) / 2;
    player.y = (BACKGROUND_H) / 2;
    player.directionRad = 0;
    player.maxSpeed = 200;
    player.oldPosition = {player.x, player.y};
    player.collisionBox = {player.x, player.y, player.w, player.h};
    renderEntities.push_back(&player);

    WorldObject rock;
    rock.texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    rock.x = BACKGROUND_W / 2 - 300;
    rock.y = BACKGROUND_H / 2 - 300;
    rock.w = 200;
    rock.h = 600;
    rock.collisionBox = {rock.x, rock.y, rock.w, rock.h};
    rock.blocksMovement = true;
    renderEntities.push_back(&rock);
    collisionEntities.push_back(&rock);
    
    WorldObject fog;
    fog.texture = loadTextureFromFile(gameRenderer, "sprites/red.png");
    fog.x = BACKGROUND_W / 2 + 300;
    fog.y = BACKGROUND_H / 2 - 200;
    fog.w = 200;
    fog.h = 400;
    fog.collisionBox = {rock.x, rock.y, rock.w, rock.h};
    fog.blocksMovement = false;
    renderEntities.push_back(&fog);
    collisionEntities.push_back(&fog);


    Renderable background;
    background.texture = loadTextureFromFile(gameRenderer, "sprites/background_simple.png");
    background.x = 0;
    background.y = 0;
    background.w = BACKGROUND_W;
    background.h = BACKGROUND_H;

    Renderable textRenderable;
    char fontSrc[] = "ttf/fixed_01.ttf";
    TTF_Font *debugFont = loadTTF(fontSrc);
    SDL_Color textColor = {0, 0, 0};

    // const std::string genericTextureSrc = "sprites/red.png";
    // const RenderObject genericTexture = loadTextureFromFile(gameRenderer, genericTextureSrc);
   
    /*
    Entity redBlock;
    redBlock.texture = genericTexture;
    // redBlock.collision_box.x = 200;
    // redBlock.collision_box.y = 500;
    // redBlock.collision_box.w = 200;
    // redBlock.collision_box.h = 200;
    collisionEntities.push_back(&redBlock);
    renderEntities.push_back(&redBlock);

    Entity walls[4];
    int wallsIndex = 4;

    // walls[0].collision_box.x = 0;
    // walls[0].collision_box.y = 0;
    // walls[0].collision_box.w = 10;
    // walls[0].collision_box.h = BACKGROUND_H;

    // walls[1].collision_box.x = BACKGROUND_W;
    // walls[1].collision_box.y = 0;
    // walls[1].collision_box.w = 10;
    // walls[1].collision_box.h = BACKGROUND_H;

    // walls[2].collision_box.x = 0;
    // walls[2].collision_box.y = 0;
    // walls[2].collision_box.w = BACKGROUND_W;
    // walls[2].collision_box.h = 10;

    // walls[3].collision_box.x = 0;
    // walls[3].collision_box.y = BACKGROUND_H;
    // walls[3].collision_box.w = BACKGROUND_W;
    // walls[3].collision_box.h = 10;

    for (int i = 0; i < 4; i++) {
        walls[i].texture = genericTexture;
        collisionEntities.push_back(&walls[i]);
        renderEntities.push_back(&walls[i]);
    }

    loadEntityArray(walls, 4, "simple_border", gameRenderer, genericTextureSrc);
    loadEntity(&redBlock, "red_block");
    */

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

        player.oldPosition.x = player.x;
        player.oldPosition.y = player.y;
        updatePlayerPosition(&player, SDL_GetKeyboardState(NULL), deltaTime);
        
        // Collisions
        for (int i = 0; i < collisionEntities.size(); i++)
        {
             handleCollision(&player, collisionEntities[i]);
        }

        // Render background
        cameraRect.x = player.x - (CAMERA_W - player.w) / 2,
        cameraRect.y = player.y - (CAMERA_H - player.h) / 2, 
        renderTextureToCamera(gameRenderer, &background, &cameraRect);
        
        // Render game objects
        for (int i = 0; i < renderEntities.size(); i++) {
            renderTextureToCamera(gameRenderer, renderEntities[i], &cameraRect);
        }

        // Top right corner game data
        playerCoordinates = "X: " + std::to_string(player.x) + "  Y: " + std::to_string(player.y);
        fpsDisplay = "FPS: " + std::to_string(avgFPS);
        timePassed = "Time Passed: " + std::to_string(SDL_GetTicks() / 1000.f) + " s";
        playerDirection = "Player direction: " + std::to_string(player.directionRad);
        playerSpeed = "Player speed x: " + std::to_string(player.x - player.oldPosition.x) + "\nPlayer speed y: " + std::to_string(player.y - player.oldPosition.y);

        textRenderable.texture = createTextureFromText(gameRenderer, debugFont, playerCoordinates, textColor);
        textRenderable.x = 10;
        textRenderable.y = 10;
        textRenderable.w = textRenderable.texture.w;
        textRenderable.h = textRenderable.texture.h;
        renderTexture(gameRenderer, &textRenderable, NULL);
        textRenderable.texture = createTextureFromText(gameRenderer, debugFont, fpsDisplay, textColor);
        textRenderable.y = 40;
        textRenderable.w = textRenderable.texture.w;
        textRenderable.h = textRenderable.texture.h;
        renderTexture(gameRenderer, &textRenderable, NULL);
        textRenderable.texture = createTextureFromText(gameRenderer, debugFont, timePassed, textColor);
        textRenderable.y = 70;
        textRenderable.w = textRenderable.texture.w;
        textRenderable.h = textRenderable.texture.h;
        renderTexture(gameRenderer, &textRenderable, NULL);
        textRenderable.texture = createTextureFromText(gameRenderer, debugFont, playerDirection, textColor);
        textRenderable.y = 100;
        textRenderable.w = textRenderable.texture.w;
        textRenderable.h = textRenderable.texture.h;
        renderTexture(gameRenderer, &textRenderable, NULL);
        textRenderable.texture = createTextureFromText(gameRenderer, debugFont, playerSpeed, textColor);
        textRenderable.y = 130;
        textRenderable.w = textRenderable.texture.w;
        textRenderable.h = textRenderable.texture.h;
        renderTexture(gameRenderer, &textRenderable, NULL);

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
