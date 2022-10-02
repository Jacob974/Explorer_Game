#pragma once
#include "datatypes.h"

/**
 * @brief figures out if a moving tile (or line) will hit a static tile and how far the moving tile will be able to move 
 * 
 * @param staticTilePos the nonmoving tile's possition
 * @param staticTileSize the nonmoving tile's size
 * @param dynamicTilePos the dynamic tile's possition
 * @param synamicTileSize the dynamic tile's size
 * @param amountMoved the dynamic tile's movement
 * @return A Vec2 of the amount the dynamic tile moves
 */
Vec2 detectTileCollision(Vec2 staticTilePos, Vec2 staticTileSize, Vec2 dynamicTilePos, Vec2 dynamicTileSize, Vec2 amountMoved);