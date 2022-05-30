#include "tileMap.h"
#include <stdlib.h>

struct Tile createTile(int xCoord, int yCoord, int w, int h, const char *imagePath, SDL_Renderer* ren)
{
    struct Tile temp;
    temp.size.x = w; 
    temp.size.y = h;
    temp.coords.x = xCoord;
    temp.coords.y = yCoord;
    temp.texture = IMG_LoadTexture(ren, imagePath);

    return temp;
}
struct TileMap createTileMap()
{
    struct TileMap tempMap;
    tempMap.amountOfTiles = 0;
    return tempMap;
}
void addTile(struct TileMap* map, struct Tile* tile)
{
    map->tiles[map->amountOfTiles] = tile;
    map->amountOfTiles++;
}
void updateTileMap(struct TileMap* tileMap, struct Entity* entity) 
{   
    //where to start rendering the ground from on the y is
    tileMap->yOffset = entity->dest.y - entity->coords.y;

    //where to start rendering the ground from on the x is
    tileMap->xOffset = entity->dest.x - entity->coords.x ; 
}
void renderTileMap(struct TileMap* tileMap, SDL_Renderer* ren)
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