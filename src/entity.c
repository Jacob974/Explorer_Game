#include "entity.h"

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
    int footHight = entity->coords.y + entity->dest.h;
    int rightSide = entity->coords.x + entity->dest.w;

    for (int w = 0; w < 32; w++) //width
    {
        for (int h = 0; h < 64; h++) //hight
        {
            //main code
            if (tileMap->tileData[w][h] == 1) //if a block exists
            {
                if(!(rightSide < (w * 32) || entity->coords.x > (w * 32 + 32))) //if entity is intersecting on the x axis
                {
                    if(!(entity->coords.y > (h * 32+32) || footHight < (h * 32))) //if entity is intersecting on the y axis
                    {
                        printf("intersection\n");
                    }
                }
            }
        }
    }
    entity->coords.x += entity->accel.x;
    entity->coords.y += entity->accel.y;

    entity->accel.x = 0;
    entity->accel.y = 0;
}