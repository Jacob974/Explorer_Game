#include "entity.h"
#include <math.h>

void createEntity(struct Entity *ent, int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer)
{
    ent->dest.x = x;
    ent->dest.y = y;
    ent->dest.w = w;
    ent->dest.h = h;

    ent->coords.x = xCoord;
    ent->coords.y = yCoord;

    ent->texture = IMG_LoadTexture(renderer, filepath);
}
void detectGroundCollision(struct Entity *entity, struct TileMap *tileMap)
{
    int xPos = entity->coords.x + entity->accel.x; //the new x coordinate before hit detection
    int yPos = entity->coords.y + entity->accel.y; //the new y coordinate before hit detection


    //loops through all the tiles
    for (int w = 0; w < 32; w++) //width
    {
        for (int h = 0; h < 64; h++) //hight
        {
            if (tileMap->tileData[w][h] == 1) //if a block exists
            {
                //detects if theres a collision
                if(!(xPos + entity->dest.w < (w * 32) || xPos > (w * 32 + 32))) //if entity is intersecting on the x axis
                {
                    if(!(yPos > (h * 32 + 32) || yPos + entity->dest.h < (h * 32))) //if entity is intersecting on the y axis
                    {
                        //determines how to move the entity 
                        printf("intersection\n");
                    }
                }
            }
        }
    }
    entity->coords.x = xPos;
    entity->coords.y = yPos;

    entity->accel.x = 0;
    entity->accel.y = 0;
}
