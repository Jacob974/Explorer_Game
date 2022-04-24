#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"
#include "tileMap.h"
/**
 * @brief Creates a Entity object
 */
void createEntity(struct Entity *ent, int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer);
/**
 *  @brief the point at which an entity collides with a tile along a vector
 *
 *  @param entAccel the length of the vector
 *  @param entPos the starting point of the vector
 *  @param tilePos the top left corner of a tile
 *  @param tileSize the width and hight of the vector
 *
 *  @return a Vec2 of the coordinates where the vector intersects the tile
 */
struct Vec2 detectCollisionPoint(struct Vec2 entAccel, struct Vec2 entPos, struct Vec2 tilePos, struct Vec2 tileSize);