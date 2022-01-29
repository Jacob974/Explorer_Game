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
 
        case SDL_KEYDOWN: // keys pressed
            switch (pollEvent.key.keysym.sym)
            {
            case SDLK_w:
                w = 1;
                break;
            case SDLK_a:
                a = 1;
                break;
            case SDLK_s:
                s = 1;
                break;
            case SDLK_d:
                d = 1;
                break;
            case SDLK_UP:
                up = 1;
                break;
            case SDLK_LEFT:
                left = 1;
                break;
            case SDLK_DOWN:
                down = 1;
                break;
            case SDLK_RIGHT:
                right = 1;
                break;
            }
            break;

        case SDL_KEYUP: // keys released
            switch (pollEvent.key.keysym.sym)
            {
            case SDLK_w:
                w = 0;
                break;
            case SDLK_a:
                a = 0;
                break;
            case SDLK_s:
                s = 0;
                break;
            case SDLK_d:
                d = 0;
                break;
            case SDLK_UP:
                up = 0;
                break;
            case SDLK_LEFT:
                left = 0;
                break;
            case SDLK_DOWN:
                down = 0;
                break;
            case SDLK_RIGHT:
                right = 0;
                break;
            }
        default:
            break;
        }
        /*update*/
        if(w)
        {
            player.accel.y = -5;
        }
        if(a)
        {
            player.accel.x = -5;
        }
        if(s)
        {
            player.accel.y = 5;
        }
        if(d)
        {
            player.accel.x = 5;
        }
        if(up)
        {
            player.dest.y -= 5;
        }
        if(left)
        {
            player.dest.x -= 5;
        }
        if(down)
        {
            player.dest.y += 5; 
        }
        if(right)
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