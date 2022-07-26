#include "tileMap.h"
#include <stdlib.h>
#include <limits.h>
TileMap createTileMap(SDL_Renderer* ren)
{
    TileMap tempMap;
    tempMap.amountOfTiles = 0;
    tempMap.renderer = ren;
    tempMap.tiles = malloc(1);
    return tempMap;
}
void addTile(TileMap* map, int x, int y, int w, int h, const char* texture)
{
    //creates a new tile
    Tile* tile = malloc(sizeof(Tile));
    tile->size.x = w;
    tile->size.y = h;
    tile->coords.x = x;
    tile->coords.y = y;
    tile->texture = IMG_LoadTexture(map->renderer, texture);

    map->amountOfTiles++;
    map->tiles = realloc(map->tiles, sizeof(Tile*) * map->amountOfTiles);
    map->tiles[map->amountOfTiles -1] = tile;
}
void destroyTileMap(TileMap* tileMap)
{
    for(int i = 0; i < tileMap->amountOfTiles; i++)
    {
        free(tileMap->tiles[i]);
    }
    free(tileMap->tiles);
}
void updateTileMap(TileMap* tileMap, Entity* entity) 
{   
    //where to start rendering the ground from on the y is
    tileMap->yOffset = entity->dest.y - (entity->coords.y);

    //where to start rendering the ground from on the x is
    tileMap->xOffset = entity->dest.x - entity->coords.x ; 
}
void renderTileMap(TileMap* tileMap, SDL_Renderer* ren)
{
    for(int i = 0; i < tileMap->amountOfTiles; i++)
    {
        SDL_Rect renderingCoords; //turns the size and possition into an ASL_Rect
        renderingCoords.x = tileMap->tiles[i]->coords.x + tileMap->xOffset;
        renderingCoords.y = tileMap->tiles[i]->coords.y + tileMap->yOffset;
        renderingCoords.h = tileMap->tiles[i]->size.y;
        renderingCoords.w = tileMap->tiles[i]->size.x;

        SDL_RenderCopy(ren, tileMap->tiles[i]->texture, NULL, &renderingCoords);
    }  
}
void generateWorld(TileMap* tileMap, int seed)
{
    srand(seed);
    Vec2 tilePos = (Vec2){.x = 0, .y = 64 + (rand() % 10)};
    Sint8 grassItr = 0; //generates tiles in a straight line until it goes to 0, then it generates 1 above or bellow
    Sint8 dirtItr = 0; //how far under the grass to generate dirt
    for(int i = 0; i < 100; i++)
    {
        if(grassItr <= 0)
        {
            switch(rand() % 3)
            {
                case 2:
                    tilePos.y -= 1;
                    break;
                case 1:
                    tilePos.y += 1;
                    break;
                default:
                    break;
            }
            grassItr = ((rand() % 5) + 1);
        }
        tilePos.x += 1;
        addTile(tileMap, tilePos.x * 32, tilePos.y * 32, 32, 32, "res/gfx/grass.png");

        // int yTilePos = tilePos.y - 1;

        // for(int i = 0; i <= rand() % 2; i++) //generates dirt under the grass
        // {
        //     addTile(tileMap, tilePos.x * 32, yTilePos * 32, 32, 32, "res/gfx/dirt.png");
        //     yTilePos--;
        // }
        // while(yTilePos > 0)
        // {
        //     addTile(tileMap, tilePos.x * 32, yTilePos * 32, 32, 32, "res/gfx/stone.png");

        // }
        grassItr--;
    }
}