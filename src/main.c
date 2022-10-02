#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "datatypes.h"
#include "utils.h"
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

    // SDL variables
    SDL_Window *window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHight, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event pollEvent;

    // creates game objects
    Entity player = createEntity(0, -64, windowWidth / 2, windowHight / 2, 32, 64, "res/gfx/entities/man_in_suit.png", renderer);
    SDL_Rect playerImageRect = (SDL_Rect){.x = 0, .y = 0, .w = 32, .h = 64};
    TileMap tileMap = createTileMap(renderer, 1000, 50); //this needs to be destroyed at the end of the program

    //animation variables
    Uint64 animationItterater = 0; //counts up each time the game update
    int animationDelay; //how many updates before the animation updates
    Uint8 animationDelayItterator; //counts down from animationDelay until it hits 0

    //mouse and keyboard variables
    Vec2 mouseCoords;
    const Uint8* keyState;

    //misc variables
    int sandbox;
    int pendingJump = 0;
    int prevAccel = 0; //prevous y accel of the player

    SDL_Texture* skyTexture = IMG_LoadTexture(renderer, "res/gfx/misc/sky.png");
    SDL_Rect skyRect = (SDL_Rect){.x = 0, .y = 0,};
    SDL_GetWindowSize(window, &skyRect.w, &skyRect.h);


    //game loop variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / fps; // times per milisecond
    animationDelay = fps / 10;
    animationDelayItterator = animationDelay;

    /*pregame computations*/
    const char* generatingWorldPath = "res/gfx/misc/generating_world.png";
    SDL_Texture* generatingWorld = IMG_LoadTexture(renderer, generatingWorldPath);
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, generatingWorld, NULL, NULL);
    SDL_RenderPresent(renderer);

    if(argc > 1)
    {
        if(!strcmp("sandbox", args[1]))
        {
            printf("sandbox\n");
            sandbox = 1;
        }
        else
        {
            sandbox = 0;
        }
    }

    generateWorld(&tileMap, time(NULL));

    /*game loop*/
    SDL_SetRenderDrawColor(renderer, 0x87, 0xCE, 0xEB, 255);
    while(gameRunning)
    {
        timeStep = SDL_GetTicks(); //time in beginning of loop

        /*polls events*/
        keyState = SDL_GetKeyboardState(NULL);
        SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
        
        /*processes mouse events*/
        while(SDL_PollEvent(&pollEvent))
        {
            /*makes sure to process all these event during this itteration of the loop so they dont build up on the event stack*/
            if(pollEvent.button.button == SDL_BUTTON_LEFT && sandbox)
            {
                if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
                {
                    Vec2 selectedTile = selectTile(&tileMap, &mouseCoords);
                    addTile(&tileMap, selectedTile.x, selectedTile.y, 1, "res/gfx/blocks/stone.png");
                }
                else
                {
                    Vec2 selectedTile = selectTile(&tileMap, &mouseCoords);
                    destroyTile(&tileMap, &selectedTile);
                }

            }
            if(pollEvent.type == SDL_QUIT)
            {
                gameRunning = 0;
            }
        }

        /*processes keyboard events*/
        if(keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W])
        {
            pendingJump = 1;
        }
        if(keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S])
        {
            //player.accel.y += 5;
        }
        if(keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D])
        {
            player.accel.x += 5;
        }
        if(keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A])
        {
            player.accel.x -= 5;
        }
        if(keyState[SDL_SCANCODE_ESCAPE])
        {
            gameRunning = 0;
        }
        if(keyState[SDL_SCANCODE_SPACE])
        {
            player.coords = (Vec2){.x = 0, .y = 0};
            player.accel.y = 0;
        }

        /* update */
        prevAccel = player.accel.y;
        detectCollisionPoint(&player, &tileMap);
         
        player.coords.x += player.accel.x;
        player.coords.y += player.accel.y;

        /*makes the player jump if the player is on the ground*/
        if(pendingJump && player.accel.y == 0 && prevAccel > 0)
        {
            player.accel.y -= 10;
        }
        pendingJump = 0;

        player.accel.y += 1;

        /*animates the player*/
        playerImageRect.x = 32 * (animationItterater % 4); //horizontally selects one of the 4 frames of the player image in order to animate the player  
        if(player.accel.x < 0) //selects the second row of panels from the player image to make the player run left
        {
            playerImageRect.y = 64;
        }
        else if(player.accel.x > 0) //selects the second row of panels from the player image to make the player run left
        {
            playerImageRect.y = 128;
        }
        else
        {
            playerImageRect.y = 0;
        }

        player.accel.x = 0;

        updateTileMap(&tileMap, &player);

        //updates the animation itterater
        animationDelayItterator--;
        if(animationDelayItterator <= 0)
        {
            animationDelayItterator = animationDelay;
            animationItterater++;
        }

        /*render*/

        SDL_RenderClear(renderer);

        //renders the tile map
        SDL_RenderCopy(renderer, skyTexture, NULL, NULL);
        SDL_RenderCopy(renderer, player.texture, &playerImageRect, &player.dest);
        renderTileMap(&tileMap, renderer);


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
      
    destroyTileMap(&tileMap);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}