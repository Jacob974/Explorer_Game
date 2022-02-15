#include "entity.h"
#include <math.h>

#define no_movement 0
#define left 1
#define right 2
#define up 1
#define down 2

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
    int xPos = entity->coords.x + entity->accel.x; // the new x coordinate before hit detection
    int yPos = entity->coords.y + entity->accel.y; // the new y coordinate before hit detection

    int xDirection = no_movement;
    int yDirection = no_movement;

    // gets the direction the entity is coming from
    if(entity->accel.x > 0)
    {
        xDirection = right;
    }
    if(entity->accel.x < 0)
    {
        xDirection = left;
    }
    if(entity->accel.y > 0)
    {
        yDirection = up;
    }
    if(entity->accel.y < 0)
    {
        yDirection = down;
    }

    // loops through all the tiles
    for (int w = 0; w < 32; w++) // width
    {
        for (int h = 0; h < 64; h++) // hight
        {
            //detects if a block is there
            if (tileMap->tileData[w][h] == 1)
            {
                //detects if theres a collision
                if (!(xPos + entity->dest.w < (w * 32) || xPos > (w * 32 + 32))) // if entity is intersecting on the x axis
                {
                    if (!(yPos > (h * 32 + 32) || yPos + entity->dest.h < (h * 32))) // if entity is intersecting on the y axis
                    {
                        printf("intersection\n");
                        //detects if there is a colision on both axies
                        if(xDirection == no_movement)
                        {
                            if(xDirection == right)
                            {
                                //(w * 32) <  ? 
                            }
                        }
                        else if(!yDirection == no_movement)
                        {

                        }
                        else
                        {

                        } 
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