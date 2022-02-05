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

    int xFinalPos; //the new x coordinate after hit detection
    int yFinalPos; //the new y coordinate after hit detection

    double xAmount; //the amount the player has moved through the block
    double yAmount; //the amount the player has moved through the block

    int fromLeft; //if it came from the left. This is a bool
    int fromTop; //if it came from the top. This is a bool

    int maxXMovement = entity->accel.x; //the maximum amount the entity can move on the x axis
    int maxYMovement = entity->accel.y; //the maximum amount the entity can move on the y axis
    
    int footHight = entity->coords.y + entity->dest.h;
    int rightSide = entity->coords.x + entity->dest.w;
    
    //determine the direction
    if(entity->accel.x >= entity->dest.x) //if entity is going right
    {
        fromLeft = 1;
    }
    else                                  //if entity is going left
    {
        fromLeft = 0;
    }
    if(entity->accel.y >= entity->dest.y) //if entity is going down
    {
        fromTop = 1;
    }
    else                                  //if entity is going up
    {
        fromTop = 0;
    }

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
                    if(!(yPos > (h * 32+32) || yPos + entity->dest.h < (h * 32))) //if entity is intersecting on the y axis
                    {
                        //determines how to move the entity 
                        printf("intersection\n");

                        //what ratio of the entities movement is outside the block
                        if(fromLeft)
                        {
                            xAmount = (double)((entity->coords.x + entity->dest.w)- (w * 32))/(double)((xPos  + entity->dest.w) - (w * 32));
                        }
                        else
                        {
                            xAmount = (double)(xPos - (w * 32 + 32))/(double)((w * 32 + 32) - xPos);
                        }
                        if(fromTop)
                        {
                            yAmount = (double)((entity->coords.y + entity->dest.h) - (h * 32))/(double)((yPos + entity->dest.h)- (h * 32));
                        }
                        else
                        {
                            yAmount = (double)(yPos - (h * 32 + 32))/(double)((h * 32 + 32) - yPos);
                        }
                        //determines what side of the block is hit first

                        if(yAmount < xAmount)
                        {
                            if(fromTop)
                            {
                                yPos = (h * 32);
                                if(yPos < yFinalPos) //only swaps final y for y if y is less
                                {
                                    yFinalPos = yPos;
                                }
                            }
                            else
                            {
                                xPos = (h * 32 + 32);
                                if(yPos > yFinalPos)
                                {
                                    yFinalPos = yPos;
                                }
                            }
                        }
                        else
                        {
                            if(fromLeft)
                            {
                                xPos = (w * 32);
                                if(xPos < xFinalPos) //only swaps final x for x if x is less
                                {
                                    xFinalPos = xPos;
                                }
                            }
                            else
                            {
                                xPos = (w * 32 + 32);
                                if(xPos > xFinalPos)
                                {
                                    xFinalPos = xPos;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    entity->coords.x = xFinalPos;
    entity->coords.y = yFinalPos;

    entity->accel.x = 0;
    entity->accel.y = 0;
}