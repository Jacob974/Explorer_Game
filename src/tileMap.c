#include "tileMap.h"
#include "gameObjects.h"
struct TileMap createTileMap(SDL_Renderer* ren)
{
    struct TileMap tempMap;
    tempMap.amountOfTiles = 0;
    tempMap.renderer = ren;
    return tempMap;
}
void addTile(struct TileMap* map, int x, int y, int w, int h, const char* texture)
{
    struct Tile* tile = malloc(sizeof(struct Tile));
    tile->size.x = w;
    tile->size.y = h;
    tile->coords.x = x;
    tile->coords.y = y;
    tile->texture = IMG_LoadTexture(map->renderer, texture);

    map->tiles[map->amountOfTiles] = tile;
    map->amountOfTiles += 1;
}
void destroyTileMap(struct TileMap* tileMap)
{
    for(int i = 0; i < tileMap->amountOfTiles; i++)
    {
        free(tileMap->tiles[i]);
    }
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