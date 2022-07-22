#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>

typedef struct Vec2
{
    int x;
    int y;
} Vec2;
typedef struct Entity
{ 
    //SDL_Rect source;
    SDL_Rect dest;
    SDL_Texture* texture;

    struct Vec2 coords; //coords
    struct Vec2 accel; //accel
} Entity;
typedef struct Tile 
{
    struct Vec2 size;
    struct Vec2 coords;
    SDL_Texture* texture;
} Tile;
typedef struct TileMap
{
    int amountOfTiles;
    int xOffset;
    int yOffset;

    SDL_Renderer* renderer;
    
    struct Tile* tiles[10]; //a string of tiles
} TileMap;