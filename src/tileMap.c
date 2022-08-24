#include "tileMap.h"
#include <stdlib.h>
#include <limits.h>
TileMap createTileMap(SDL_Renderer* ren, int width, int hight)
{
    // TileMap tempMap;

    // tempMap.amountOfTiles = 0;
    // tempMap.renderer = ren;
    // tempMap.tiles = malloc(1);

    // return tempMap;

    TileMap tileMap;

    tileMap.renderer = ren;
    tileMap.tileHight = hight;
    tileMap.tileWidth = width;

    tileMap.tileList = malloc(sizeof(Tile) * width * hight);

    tileMap.xOffset = 0;
    tileMap.yOffset = 0;

    return tileMap;
}
void addTile(TileMap* tileMap, int x, int y, const char* texture)
{
    //creates a new tile
    // Tile* tile = malloc(sizeof(Tile));
    // tile->coords.x = x;
    // tile->coords.y = y;
    // tile->texture = IMG_LoadTexture(tileMap->renderer, texture);

    // tileMap->amountOfTiles++;
    // tileMap->tiles = realloc(tileMap->tiles, sizeof(Tile*) * tileMap->amountOfTiles);
    // tileMap->tiles[tileMap->amountOfTiles -1] = tile;

    //new code
    if(x >= 0 && y >= 0 && x < tileMap->tileWidth && y < tileMap->tileHight)
    {
        int inc = tileMap->tileHight * x + y;
        tileMap->tileList[inc].coords.x = x;
        tileMap->tileList[inc].coords.y = y;

        tileMap->tileList[inc].exists = 1;
        tileMap->tileList[inc].texture = IMG_LoadTexture(tileMap->renderer, texture);
    }
    else
    {
        printf("failed to generate tile\n");
    }
}
void destroyTileMap(TileMap* tileMap)
{
    for(int i = 0; i < tileMap->tileWidth; i++)
    {
        for(int j = 0; j < tileMap->tileHight; j++)
        {
            destroyTile(tileMap, &(Vec2){.x = i, .y = j});
        }
    }
    free(tileMap->tileList);
}
void updateTileMap(TileMap* tileMap, Entity* entity) 
{   
    //where to start rendering the ground from on the y is
    tileMap->yOffset = entity->dest.y - entity->coords.y;

    //where to start rendering the ground from on the x is
    tileMap->xOffset = entity->dest.x - entity->coords.x ; 
}
void renderTileMap(TileMap* tileMap, SDL_Renderer* ren)
{
    // for(int i = 0; i < tileMap->amountOfTiles; i++)
    // {
    //     SDL_Rect renderingCoords; //turns the size and possition into an SDL_Rect
    //     renderingCoords.x = tileMap->tiles[i]->coords.x * 32 + tileMap->xOffset;
    //     renderingCoords.y = tileMap->tiles[i]->coords.y * 32 + tileMap->yOffset;
    //     if(renderingCoords.x < 1500 && renderingCoords.y < 1000 && renderingCoords.x > -32 && renderingCoords.y > -32)
    //     {
    //         renderingCoords.h = 32;
    //         renderingCoords.w = 32;
    
    //         SDL_RenderCopy(ren, tileMap->tiles[i]->texture, NULL, &renderingCoords);
    //     }
    // }
    for(int i = 0; i < tileMap->tileHight * tileMap->tileWidth; i++)
    {
        if((tileMap->tileList[i].exists == 1) && &tileMap->tileList[i].texture != NULL)
        {
            SDL_Rect renderingCoords;
            renderingCoords.h = 32;
            renderingCoords.w = 32;
            renderingCoords.x = tileMap->tileList[i].coords.x * 32 + tileMap->xOffset;
            renderingCoords.y = tileMap->tileList[i].coords.y * 32 + tileMap->yOffset;

            SDL_RenderCopy(tileMap->renderer, tileMap->tileList[i].texture, NULL, &renderingCoords);
        }
    }
}
Vec2 selectTile(TileMap* tileMap, Vec2* mouseCoords)
{
    Vec2 selectedTileCoord;

    selectedTileCoord.x = (mouseCoords->x - tileMap->xOffset) / 32;
    selectedTileCoord.y = (mouseCoords->y - tileMap->yOffset) / 32;

    return selectedTileCoord;
}
void destroyTile(TileMap* tileMap, Vec2* tileCoords)
{
    if(tileMap->tileList[tileCoords->x * tileMap->tileHight + tileCoords->y].exists == 1)
    {
        tileMap->tileList[tileCoords->x * tileMap->tileHight + tileCoords->y].exists = 0;
        SDL_DestroyTexture(tileMap->tileList[tileCoords->x * tileMap->tileHight + tileCoords->y].texture);
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
                    if(tilePos.y > 0)
                        tilePos.y -= 1;
                    break;
                default:
                    break;
            }
            grassItr = ((rand() % 5) + 1);
        }
        addTile(tileMap, tilePos.x, tilePos.y, "res/gfx/grass.png");

        dirtItr = (rand() % 2) + 1;
        int prevYTilePos = tilePos.y; //makes sure we can continue where we left off when it comes to generating the grass
        
        /*generates the dirt*/
        for(int i = 0; i < dirtItr; i++)
        {
            tilePos.y++;
            addTile(tileMap, tilePos.x, tilePos.y, "res/gfx/dirt.png");
        }

        /*generates the stone*/
        while(tilePos.y < 30)
        {
            tilePos.y++;
            addTile(tileMap, tilePos.x, tilePos.y, "res/gfx/stone.png");
        }

        tilePos.y = prevYTilePos;
        grassItr--;
        tilePos.x++;
    }
}