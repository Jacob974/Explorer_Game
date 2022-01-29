#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"
 
void createTile(struct Tile* tile, int w, int h, SDL_Renderer* ren);
void createTileMap(struct TileMap* tileMap, struct Tile* tile, int mapData[32][64]);
void updateTileMap(struct TileMap* tileMap, struct Entity* entity);
void renderTileMap(struct TileMap* tileMap, SDL_Renderer* ren);