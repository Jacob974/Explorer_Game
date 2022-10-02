#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "datatypes.h"
#include "utils.h"
#include "tileMap.h"
/**
 * @brief Creates a Entity object
 * 
 * @param xCoord X coordinate of the entity in gamespace
 * @param yCoord Y coordinate of the entity in gamespace 
 * @param x X coordinate of the entity in screenscace
 * @param y Y coordinate of the entity in screenspace
 * @param w width of entity
 * @param h hight of entity
 * @param filepath file path of the texture of the entity
 * @param renderer the SDL_Renderer used by the game
 */
Entity createEntity(int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer);
/**
 * @brief digs dirt
 * 
 * @param tileMap a pointer to the tileMap
 * @param entity a pointer to the entity
 * @param endOfSelection the point in coordinate space where the ray that selects the tile is. the starting pointn if the player's head
 */
void digTile(TileMap* tileMap, Entity* entity, Vec2 endOfSelection);
/**
 *  @brief Corrects the accel of the entity so that it doesnt collide with the tile map
 *
 *  @param entity a pointer to the entity object
 *  @param tileMap a pointer to the tiles map the entity is being tested against
 */
void detectCollisionPoint(Entity* entity, TileMap* tileMap);