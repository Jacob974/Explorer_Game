#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "gameObjects.h"
#include "entity.h"
#include "tileMap.h"

#include "tempMap.h"

int main(int argc, char *args[]) 
{
    SDL_Init(0);

    /*variables*/

    // window variables
    const char *title = "Explorer Game";
    int windowHight = 700;
    int windowWidth = 1100;
    int gameRunning = 1;

    // creates SDL objects
    SDL_Window *window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHight,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event pollEvent;

    // game objects
    struct Entity player = createEntity(0, 50, windowWidth / 2, windowHight / 2, 32, 64, "res/gfx/greenEntity.png", renderer);

    //tiles
    struct Tile tile1 = createTile(0, 0, 32, 32,   "res/gfx/redTile.png", renderer);
    struct Tile tile2 = createTile(32, 0, 32, 32,  "res/gfx/redTile.png", renderer);
    struct Tile tile3 = createTile(64, 0, 32, 32,  "res/gfx/redTile.png", renderer);
    struct Tile tile4 = createTile(96, 0, 32, 32,  "res/gfx/redTile.png", renderer);
    struct Tile tile5 = createTile(96, 32, 32, 32, "res/gfx/redTile.png", renderer);
    struct Tile tile6 = createTile(96, 64, 32, 32, "res/gfx/redTile.png", renderer);


    
    //tile map
    struct TileMap tileMap = createTileMap();
    addTile(&tileMap, &tile1);
    addTile(&tileMap, &tile2);
    addTile(&tileMap, &tile3);
    addTile(&tileMap, &tile4);
    addTile(&tileMap, &tile5);
    addTile(&tileMap, &tile6);

    struct Vec2 entPos = (struct Vec2){.x = windowWidth/2, .y = windowHight/2};
    struct Vec2 tilePos = (struct Vec2){.x = 800, .y = 290};
    struct Vec2 tileSize = (struct Vec2){.x = 32, .y = 32};

    struct Vec2 mouseCoords;
    const Uint8* keyState;

    // timestep variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / 60; // times per milisecond

    // misc

    /*game loop*/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    while (gameRunning)
    {
        timeStep = SDL_GetTicks(); // time in beginning of loop

        /*poll events*/
        SDL_PollEvent(&pollEvent);

        SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
        if(pollEvent.type == SDL_QUIT)
        {
            gameRunning = 0;
        }
        keyState = SDL_GetKeyboardState(NULL);
        if(keyState[SDL_SCANCODE_UP])
        {
            player.accel.y -= 5;
        }
        if(keyState[SDL_SCANCODE_DOWN])
        {
            player.accel.y += 5;
        }
        if(keyState[SDL_SCANCODE_RIGHT])
        {
            player.accel.x += 5;
        }
        if(keyState[SDL_SCANCODE_LEFT])
        {
            player.accel.x -= 5;
        }

        if(keyState[SDL_SCANCODE_ESCAPE])
        {
            gameRunning = 0;
        }

        /* update */
        for(int i = 0; i < tileMap.amountOfTiles; i++)
        {
            player.accel = detectCollisionPoint(player.accel, player.coords, (struct Vec2){.x = player.dest.w, .y = player.dest.h}, tileMap.tiles[i]->coords, tileMap.tiles[i]->size);    
        }
         
        player.coords.x += player.accel.x;
        player.coords.y += player.accel.y;

        player.accel.y = 0;
        player.accel.x = 0;

        updateTileMap(&tileMap, &player);

        /*render*/

        SDL_RenderClear(renderer);

        //renders the tile map
        //renderTileMap(&tileMap, renderer);
        renderTileMap(&tileMap, renderer);
        SDL_RenderCopy(renderer, player.texture, NULL, &player.dest);


        SDL_RenderPresent(renderer);

        /*pauses the game to make it 60 fps*/
        if ((SDL_GetTicks() - timeStep) < frameLength)
        {
            SDL_Delay(timeStep + frameLength - SDL_GetTicks()); 
        }
        else
        {
            printf("too fast!!!\n");
        }
        /*print*/
        if(argc > 1)
        {
            printf("xCoord: %d\n yCoord: %d\n\n", player.coords.x, player.coords.y);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}