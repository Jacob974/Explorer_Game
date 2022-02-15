#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "gameObjects.h"
#include "entity.h"
#include "tileMap.h"

#include "tempMap.h"

int main(int argc, char *args[]) 
{
    SDL_Init;

    /*variables*/

    // window variables
    const char *title = "Explorer Game";
    int windowHight = 700;
    int windowWidth = 1100;

    // game running
    int gameRunning = 1;

    // key pressed variables
    int w = 0;
    int a = 0;
    int s = 0;
    int d = 0;

    int up = 0; 
    int left = 0;
    int down = 0;
    int right = 0;

    // creates SDL objects
    SDL_Window *window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHight,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event pollEvent;
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    /*game objects*/ 

    struct Entity player; createEntity(&player, 0, -64, windowWidth/2, windowHight/2, 32, 64, "res/gfx/guy.png", renderer);
    struct Tile tile; createTile(&tile, 32, 32, renderer);
    struct TileMap tileMap; createTileMap(&tileMap, &tile, tempMap);

    // timestep variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / 60; // times per milisecond

    /*game loop*/

    while (gameRunning)
    {
        timeStep = SDL_GetTicks(); // time in beginning of loop

        /*poll events*/
        SDL_PollEvent(&pollEvent);

        switch (pollEvent.type)
        {
        case SDL_QUIT: 
            gameRunning = 0;
            break;
        }
        //gets key events and updates the player movement
        if(keyState[SDL_SCANCODE_W])
        {
            player.accel.y = -5;
        }
        if(keyState[SDL_SCANCODE_A])
        {
            player.accel.x = -5;
        }
        if(keyState[SDL_SCANCODE_S])
        {
            player.accel.y = 5;
        }
        if(keyState[SDL_SCANCODE_D])
        {
            player.accel.x = 5;
        }
        if(keyState[SDL_SCANCODE_UP])
        {
            player.dest.y -= 5;
        }
        if(keyState[SDL_SCANCODE_DOWN])
        {
            player.dest.y += 5;
        }
        if(keyState[SDL_SCANCODE_LEFT])
        {
            player.dest.x -= 5;
        }
        if(keyState[SDL_SCANCODE_RIGHT])
        {
            player.dest.x += 5;
        }
     
        updateTileMap(&tileMap, &player); // tile map gets updated
        detectGroundCollision(&player, &tileMap);

        /*render*/
        if(argc > 1){printf("x = %d and y = %d\n", player.coords.x, player.coords.y);}
        
        SDL_RenderClear(renderer);

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
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}