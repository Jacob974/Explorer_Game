#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"

TileMap createTileMap(SDL_Renderer* ren);

void addTile(TileMap* map, int x, int y, int w, int h, const char* texture);
void destroyTileMap(TileMap* tileMap);

void updateTileMap(TileMap* tileMap, Entity* entity);
void renderTileMap(TileMap* tileMap, SDL_Renderer* ren);