#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Vec2
{
    int x;
    int y;
};
struct Entity
{ 
    //SDL_Rect source;
    SDL_Rect dest;
    SDL_Texture* texture;

    struct Vec2 coords; //coords
    struct Vec2 accel; //accel
};
struct Tile 
{
    struct Vec2 size;
    struct Vec2 coords;
    SDL_Texture* texture;
};
struct TileMap
{
    int amountOfTiles;

    int xOffset;
    int yOffset;
    
    struct Tile* tiles[10]; //a string of tiles
};