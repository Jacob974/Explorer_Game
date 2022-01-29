#include "tileMap.h"

void createTile(struct Tile* tile, int w, int h, SDL_Renderer* ren)
{
    tile->dest.w = w; 
    tile->dest.h = h;
    tile->texture = IMG_LoadTexture(ren, "res/gfx/dirt.png");
}
void createTileMap(struct TileMap* tileMap, struct Tile* tile, int mapData[32][64])
{
    tileMap->tile = *tile; //gets the tile info
    for(int w = 0; w < 32; w++) //puts data from map into the TileMap struct
    {
        for(int h = 0; h < 64; h++)
        {
            tileMap->tileData[w][h] = mapData[w][h];
        }
    }
} 
void updateTileMap(struct TileMap* tileMap, struct Entity* entity) 
{   
    //where to start rendering the ground from on the y is
    tileMap->yOffset = entity->dest.y - entity->coords.y;

    //where to start rendering the ground from on the x is
    tileMap->xOffset = entity->dest.x - entity->coords.x; 
}
void renderTileMap(struct TileMap* tileMap, SDL_Renderer* ren)
{
    for(int w = 0; w < 32; w++) //puts data from map into the TileMap struct 
    {
        for(int h = 0; h < 64; h++) 
        {
            if(tileMap->tileData[w][h] == 1) 
            {
                tileMap->tile.dest.x = (w * 32) + tileMap->xOffset; //possition of tile
                tileMap->tile.dest.y = (h * 32) + tileMap->yOffset;
                SDL_RenderCopy(ren, tileMap->tile.texture, NULL, &tileMap->tile.dest);
            }
        }
    }
    
}