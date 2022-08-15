#include "tileMap.h"
#include <stdlib.h>
#include <limits.h>
TileMap createTileMap(SDL_Renderer* ren, int width, int hight)
{
    TileMap tempMap;

    //new code
    tempMap.tileMapWidth = width;
    tempMap.tileMapHight = hight;
    tempMap.tileList = malloc(width * hight * sizeof(Tile*));

    tempMap.amountOfTiles = 0;
    tempMap.renderer = ren;
    tempMap.tiles = malloc(1);

    return tempMap;
}
void addTile(TileMap* tileMap, int x, int y, const char* texture)
{
    //creates a new tile
    Tile* tile = malloc(sizeof(Tile));
    tile->coords.x = x;
    tile->coords.y = y;
    tile->texture = IMG_LoadTexture(tileMap->renderer, texture);

    tileMap->amountOfTiles++;
    tileMap->tiles = realloc(tileMap->tiles, sizeof(Tile*) * tileMap->amountOfTiles);
    tileMap->tiles[tileMap->amountOfTiles -1] = tile;

    //new code
    if(x >= 0 && y >= 0 && x < tileMap->tileMapWidth && y < tileMap->tileMapHight)
    {
        Tile* currentTile = malloc(sizeof(Tile*));
        currentTile->texture = IMG_LoadTexture(tileMap->renderer, texture);
        tileMap->tileList[tileMap->tileMapHight * x + y] = currentTile;
    }
    else
    {
        printf("failed to generate tile at %d, %d\n", x, y);
    }
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
        renderingCoords.x = tileMap->tiles[i]->coords.x * 32 + tileMap->xOffset;
        renderingCoords.y = tileMap->tiles[i]->coords.y * 32 + tileMap->yOffset;
        renderingCoords.h = 32;
        renderingCoords.w = 32;

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