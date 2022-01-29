#pragma once
struct Vec2f
{
    int x;
    int y;
};
struct Entity
{ 
    //SDL_Rect source;
    SDL_Rect dest;
    SDL_Texture* texture;

    struct Vec2f coords; //coords
    struct Vec2f accel; //accel
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