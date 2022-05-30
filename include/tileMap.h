#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"
 
struct Tile createTile(int xCoord, int yCoord, int w, int h, const char *imagePath, SDL_Renderer* ren);
struct TileMap createTileMap();
void addTile(struct TileMap* map, struct Tile* tile);
void updateTileMap(struct TileMap* tileMap, struct Entity* entity);
void renderTileMap(struct TileMap* tileMap, SDL_Renderer* ren);