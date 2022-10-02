#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>

/**
 *  @brief a datatype that holds two integers
 */
typedef struct Vec2
{
    int x;
    int y;
} Vec2;
/**
 *  @brief a datatype that holds data about an entity including possition, size, texture, and movement
 */
typedef struct Entity
{ 
    //SDL_Rect source;
    SDL_Rect dest;
    SDL_Texture* texture;

    Vec2 coords; //coords
    Vec2 accel; //accel

    int prevAcccel; //needed for jumping
} Entity;
/**
 *  @brief a datatype that holds data about an tile including possition, size, texture
 */
typedef struct Tile 
{
    int collidable; //if entities collide with it
    int exists; //whether or not the tile should be ignored or not

    Vec2 coords;
    SDL_Rect renderingCoords; //holds the coords of where to render the tile

    int diggable; //whether or not it can be dug

    SDL_Texture* texture;
} Tile;
/**
 *  @brief a datatype that holds data about an item which can be on the ground sometimes
 */
typedef struct Item
{
    SDL_Texture* texture;
    Vec2 pos;
} Item;
/**
 *  @brief a datatype that holds a list of tiles and info about them
 */
typedef struct TileMap
{
    Tile* tileList;

    int tileWidth;
    int tileHight;

    int xOffset;
    int yOffset;

    SDL_Renderer* renderer;
} TileMap;