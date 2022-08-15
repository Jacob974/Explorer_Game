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
    Vec2 tilePos = (Vec2){.x = 0, .y = 5};
    Sint8 grassItr = 0; //generates tiles in a straight line until it goes to 0, then it generates 1 above or bellow
    Sint8 dirtItr = 0; //how far under the grass to generate dirt

    /*generates the grass*/
    for(int i = 0; i < 1000; i++)
    {
        if(grassItr <= 0)
        {
            switch(rand() % 3)
            {
                case 2:
                    tilePos.y += 1;
                    break;
                case 1:
                    tilePos.y -= 1;
                    break;
                default:
                    break;
            }
            grassItr = ((rand() % 5) + 1);
        }
        tilePos.x++;
        addTile(tileMap, tilePos.x * 32, tilePos.y * 32, 32, 32, "res/gfx/grass.png");

        dirtItr = (rand() % 2) + 1;
        int prevYTilePos = tilePos.y; //makes sure we can continue where we left off when it comes to generating the grass
        
        /*generates the dirt*/
        for(int i = 0; i < dirtItr; i++)
        {
            tilePos.y++;
            addTile(tileMap, tilePos.x * 32, tilePos.y * 32, 32, 32, "res/gfx/dirt.png");
        }

        /*generates the stone*/
        while(tilePos.y < 30)
        {
            tilePos.y++;
            addTile(tileMap, tilePos.x * 32, tilePos.y * 32, 32, 32, "res/gfx/stone.png");
        }

        tilePos.y = prevYTilePos;
        grassItr--;
    }
    for(int i = 0; i < 20; i++) //generates some bricks
    {
        tilePos.x++;
        addTile(tileMap, tilePos.x * 32, tilePos.y * 32, 32, 32, "res/gfx/brick.png");
    }
}