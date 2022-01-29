#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameObjects.h"
#include "tileMap.h"

void createEntity(struct Entity* ent, int xCoord, int yCoord, int x, int y, int w, int h, const char* filepath, SDL_Renderer* renderer);
void detectGroundCollision(struct Entity* entity, struct TileMap* tileMap);