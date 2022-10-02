#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "datatypes.h"

/**
 * @brief Creates a Tile Map object
 * 
 * @param ren the renderer
 * @param width total width of the map in blocks
 * @param hight total hight of the map in blocks
 */
TileMap createTileMap(SDL_Renderer* ren, int width, int hight);

/**
 * @brief Adds a tile to the tile map
 * 
 * @param tileMap a pointer to the tile map the block is being added to
 * @param x x possition of the block
 * @param y y possition of the block
 * @param collidable 
 * @param texture 
 */
void addTile(TileMap* tileMap, int x, int y, int collidable, const char* texture);
/**
 * @brief Frees the memory associated with the tile map
 * 
 * @param tileMap a pointer to the tile map being destroyed
 */
void destroyTileMap(TileMap* tileMap);

/**
 * @brief Updates where on the screen the tile map should ve rendered with respect to an entity
 * 
 * @param tileMap a pointer to the tile map
 * @param entity a pointer to the entity
 */
void updateTileMap(TileMap* tileMap, Entity* entity);
/**
 * @brief Renders the tile map
 * 
 * @param tileMap a pointer to the tile map
 * @param ren the renderer
 */
void renderTileMap(TileMap* tileMap, SDL_Renderer* ren);

/**
 * @brief Gets the possition of the tile the mouse is above
 * 
 * @param tileMap //pointer to the tile map
 * @param mouseCoords //pointer to a vector of the coordinates of the mouse
 * @return Vec2 
 */
Vec2 selectTile(TileMap* tileMap, Vec2* mouseCoords);
/**
 * @brief Destroys a tile
 * 
 * @param tileMap a pointer to the tile map that contains the tile
 * @param tileCoords a pointer to a vector of the coordinates of the tile
 */
void destroyTile(TileMap* tileMap, Vec2* tileCoords);

/**
 * @brief Generates the of a tile
 * 
 * @param tileMap a pointer to the tile map of the world being generated
 * @param seed //the seed of the world
 */
void generateWorld(TileMap* tileMap, int seed);