#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"
#include "entity.h"
#include "tileMap.h"


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

    // creates game objects
    Entity player = createEntity(0, -100, windowWidth / 2, windowHight / 2, 32, 64, "res/gfx/greenEntity.png", renderer);
    TileMap tileMap = createTileMap(renderer); //this needs to be destroyed at the end of the program

    //misc variables
    Sint8 pendingJump = 0;
    Uint64 itterate = 0; //counts up each time the game update

    //adds tiles to map
    addTile(&tileMap, 0, 0, 32, 32,   "res/gfx/redTile.png");
    addTile(&tileMap, 32, 0, 32, 32,  "res/gfx/redTile.png");
    addTile(&tileMap, 64, 0, 32, 32,  "res/gfx/redTile.png");
    addTile(&tileMap, 96, 0, 32, 32,  "res/gfx/redTile.png");
    addTile(&tileMap, 96, 32, 32, 32, "res/gfx/redTile.png");
    addTile(&tileMap, 96, 64, 32, 32, "res/gfx/redTile.png");
    
    //mouse and keyboard variables
    Vec2 mouseCoords;
    const Uint8* keyState;

    // game loop variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / 60; // times per milisecond

    /*game loop*/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    while(gameRunning)
    {
        timeStep = SDL_GetTicks(); //time in beginning of loop

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
            pendingJump = 1;
        }
        if(keyState[SDL_SCANCODE_DOWN])
        {
            //player.accel.y += 5;
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
        if(keyState[SDL_SCANCODE_SPACE])
        {
            player.coords = (Vec2){.x = 32, .y = -100};
        }

        /* update */
        detectCollisionPoint(&player, &tileMap);
         
        player.coords.x += player.accel.x;
        player.coords.y += player.accel.y;

        if(pendingJump && player.accel.y == 0)
        {
            player.accel.y -= 10;
        }
        pendingJump = 0;

        player.accel.y += 1;
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
        itterate++;
    }

    destroyTileMap(&tileMap);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}