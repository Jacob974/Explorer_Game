#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    /*renders "Generating World" while world is loading*/
    const char* generatingWorldPath = "res/gfx/generating_world.png";
    SDL_Texture* generatingWorld = IMG_LoadTexture(renderer, generatingWorldPath);
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, generatingWorld, NULL, NULL);
    SDL_RenderPresent(renderer);

    // creates game objects
    Entity player = createEntity(32, -300, windowWidth / 2, windowHight / 2, 32, 64, "res/gfx/man_in_suit.png", renderer);
    SDL_Rect playerImageRect = (SDL_Rect){.x = 0, .y = 0, .w = 32, .h = 64};
    TileMap tileMap = createTileMap(renderer); //this needs to be destroyed at the end of the program

    //misc variables
    Sint8 pendingJump = 0;
    Uint64 animationItterater = 0; //counts up each time the game update
    int animationDelay; //how many updates before the animation updates
    int prevAccel = 0; //prevous y accel of the player
    Uint8 animationDelayItterator; //counts down from animationDelay until it hits 0

    //adds tiles to map
    generateWorld(&tileMap, time(NULL));
    
    //mouse and keyboard variables
    Vec2 mouseCoords;
    const Uint8* keyState;

    // game loop variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / fps; // times per milisecond
    animationDelay = fps / 10;
    animationDelayItterator = animationDelay;
    printf("works to here\n");

    /*game loop*/
    SDL_SetRenderDrawColor(renderer, 0x87, 0xCE, 0xEB, 255);
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
            player.coords = (Vec2){.x = 32, .y = -300};
        }

        /* update */
        prevAccel = player.accel.y;
        detectCollisionPoint(&player, &tileMap);
         
        player.coords.x += player.accel.x;
        player.coords.y += player.accel.y;

        if(pendingJump && player.accel.y == 0 && prevAccel > 0)
        {
            player.accel.y -= 10;
        }
        pendingJump = 0;

        player.accel.y += 1;
        playerImageRect.x = 32 * (animationItterater % 4);
        if(player.accel.x < 0)
        {
            playerImageRect.y = 64;
        }
        else if(player.accel.x > 0)
        {
            playerImageRect.y = 128;
        }
        else
        {
            playerImageRect.y = 0;
        }

        player.accel.x = 0;

        updateTileMap(&tileMap, &player);

        animationDelayItterator--;
        //updates the animation itterater
        if(animationDelayItterator <= 0)
        {
            animationDelayItterator = animationDelay;
            animationItterater++;
        }

        /*render*/

        SDL_RenderClear(renderer);

        //renders the tile map
        renderTileMap(&tileMap, renderer);
        SDL_RenderCopy(renderer, player.texture, &playerImageRect, &player.dest);


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

    destroyTileMap(&tileMap);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}