#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"

struct TileMap createTileMap(SDL_Renderer* ren);

void addTile(struct TileMap* map, int x, int y, int w, int h, const char* texture);
void destroyTileMap(struct TileMap* tileMap);

void updateTileMap(struct TileMap* tileMap, struct Entity* entity);
void renderTileMap(struct TileMap* tileMap, SDL_Renderer* ren);