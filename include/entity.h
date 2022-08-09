#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "datatypes.h"
#include "tileMap.h"
/**
 * @brief Creates a Entity object
 */
Entity createEntity(int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer);
/**
 *  @brief Corrects the accel of the entity so that it doesnt collide with the tile map
 *
 *  @param entity a pointer to the entity object
 *  @param tileMap a pointer to the tiles map the entity is being tested against
 */
void detectCollisionPoint(Entity* entity, TileMap* tileMap);
/**
 * @brief Decides how much to move the entity
 * 
 * @param entity a pointer to the entity
 * @param movement the amount the entity moves along the x axis
 * @param jump whether or not the entitiy has jumped or not. 0 for no, 1 for yes
 */
void moveEntity(Entity* entity, int movement, Sint8 jump);