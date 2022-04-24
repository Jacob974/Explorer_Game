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

    // game objects
    struct Vec2 entPos = (struct Vec2){.x = windowWidth/2, .y = windowHight/2};
    struct Vec2 tilePos = (struct Vec2){.x = 800, .y = 290};
    struct Vec2 tileSize = (struct Vec2){.x = 80, .y = 60};

    struct Vec2 mainLine;
    struct Vec2 intersectedLine;

    struct Vec2 mouseCoords;

    // creates SDL objects
    SDL_Window *window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHight,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event pollEvent;

    const Uint8* keyState;

    // timestep variables
    unsigned long timeStep = 0; 
    int fps = 60;
    int frameLength = 1000 / 60; // times per milisecond

    // misc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    /*game loop*/

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
            tilePos.y -= 5;
        }
        if(keyState[SDL_SCANCODE_DOWN])
        {
            tilePos.y += 5;
        }
        if(keyState[SDL_SCANCODE_RIGHT])
        {
            tilePos.x += 5;
        }
        if(keyState[SDL_SCANCODE_LEFT])
        {
            tilePos.x -= 5;
        }
        

        /* update */
        struct Vec2 temp;
        struct Vec2 otherTemp = (struct Vec2){.x = mouseCoords.x - entPos.x, .y = mouseCoords.y - entPos.y};
        temp = detectCollisionPoint(otherTemp, entPos, tilePos, tileSize);
        
        /*render*/

        SDL_RenderClear(renderer);

        //renders the tile
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawLine(renderer, tilePos.x, tilePos.y, tilePos.x + tileSize.x, tilePos.y);
        SDL_RenderDrawLine(renderer, tilePos.x, tilePos.y, tilePos.x, tilePos.y + tileSize.y);
        SDL_RenderDrawLine(renderer, tilePos.x, tilePos.y + tileSize.y, tilePos.x + tileSize.x, tilePos.y + tileSize.y);
        SDL_RenderDrawLine(renderer, tilePos.x + tileSize.x, tilePos.y,  tilePos.x + tileSize.x, tilePos.y + tileSize.y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //renders a line from 0,0 to the mouse
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, entPos.x, entPos.y, temp.x, temp.y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //renders a circle where the point intersects

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
        
    
        double leftXRatio = ((double)(tilePos.x - entPos.x) / (double)(mouseCoords.x - entPos.x));
        double rightXRatio = ((double)(tilePos.x + tileSize.x - entPos.x) / (double)(mouseCoords.x - entPos.x));
        double topYRatio = ((double)(tilePos.y - entPos.y) / (double)(mouseCoords.y - entPos.y));
        double bottomYRatio = ((double)(tilePos.y + tileSize.y - entPos.y) / (double)(mouseCoords.y - entPos.y));

        printf("near x ratio = %f\n", leftXRatio);
        printf("far y ratio = %f\n", topYRatio);
        printf("|\n|\n");
        printf("near y ratio = %f\n", bottomYRatio);
        printf("far x ratio = %f\n", rightXRatio);
        
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}