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
    SDL_Rect dest;
    SDL_Texture* texture;
};
struct TileMap
{
    int xOffset;
    int yOffset;
    struct Tile tile;
    int tileData[32][64];
};