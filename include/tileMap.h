#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "datatypes.h"

TileMap createTileMap(SDL_Renderer* ren, int width, int hight);

void addTile(TileMap* map, int x, int y, const char* texture);
void destroyTileMap(TileMap* tileMap);

void updateTileMap(TileMap* tileMap, Entity* entity);
void renderTileMap(TileMap* tileMap, SDL_Renderer* ren);

void generateWorld(TileMap* tileMap, int seed);