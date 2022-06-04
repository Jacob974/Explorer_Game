#include "entity.h"

struct Entity createEntity(int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer)
{
    struct Entity temp;
    temp.dest.x = x;
    temp.dest.y = y;
    temp.dest.w = w;
    temp.dest.h = h;

    temp.coords.x = xCoord;
    temp.coords.y = yCoord;
    temp.texture = IMG_LoadTexture(renderer, filepath);

    return temp;
}
struct Vec2 detectCollisionPoint(struct Vec2 entAccel, struct Vec2 entPos, struct Vec2 entSize, struct Vec2 tilePos, struct Vec2 tileSize)
{
    struct Vec2 collisionPoint = entPos;

    /* Which side of the tile the line intersects. This is based on whether the accel is negetive or not */
    int xIntersectedSide = (entAccel.x < 0 ? tilePos.x + tileSize.x : tilePos.x); //right/left
    int yIntersectedSide = (entAccel.y < 0 ? tilePos.y + tileSize.y : tilePos.y); //bottom/top

    /*multiplies the equation by either 1 or -1 depending on the equation in order to get an absolute distance*/
    int xDirectionMultiplier = entAccel.x < 0 ? -1 : 1;
    int yDirectionMultiplier = entAccel.y < 0 ? -1 : 1;

    struct Vec2 entityCorners[4];
                entityCorners[0] = entPos;
                entityCorners[1] = (struct Vec2){.x = entPos.x, .y = entPos.y + entSize.y};
                entityCorners[2] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y};
                entityCorners[3] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y + entSize.y};

    for(int i = 0; i < 4; i++)
    {
        /*the for loop starts here*/
        struct Vec2 itteratedAccel;
        
        /* How far along the vector each side is. The sides are represented as their . 
        These equations return the position of the specific point of the tile minus the coordinate of the entity.
        The number is then divided by the acceleration amount for that side.
        If the accel is 0, the whole number is turned into 0 since you cant divide by 0 normally*/
        double leftXRatio = ((double)(tilePos.x - entityCorners[i].x) / (double)(entAccel.x));
        double rightXRatio = ((double)(tilePos.x + tileSize.x - entityCorners[i].x) / (double)(entAccel.x));
        double topYRatio = ((double)(tilePos.y - entityCorners[i].y) / (double)(entAccel.y));
        double bottomYRatio = ((double)(tilePos.y + tileSize.y - entityCorners[i].y) / (double)(entAccel.y));


        /* This determines which point is nearest and farthest away from the origin.
        The near ratio gets the smallest of the two ratios for that side, and for the far side vise versa */
        double nearYRatio = (topYRatio < bottomYRatio ? topYRatio : bottomYRatio);
        double nearXRatio = (leftXRatio < rightXRatio ? leftXRatio : rightXRatio);
        double farYRatio = (topYRatio >= bottomYRatio ? topYRatio : bottomYRatio);
        double farXRatio = (leftXRatio >= rightXRatio ? leftXRatio : rightXRatio);

        /* Determines which side the vector hits first */
        if(nearXRatio > nearYRatio) //hits a horizontel line
        {
            if((nearXRatio < 1.0) && (nearXRatio < farYRatio) && (nearXRatio >= 0))//detects if theres actually a collision
            {
                itteratedAccel.x = xIntersectedSide - entityCorners[i].x;
            }
            else
            {
                itteratedAccel.x = entAccel.x;
            }
            itteratedAccel.y = entAccel.y;
        }
        else //hits the vertical line
        {
            
            if((nearYRatio < 1.0) && (nearYRatio < farXRatio) && (nearYRatio >= 0))//detects if theres actually a collision
            {
                itteratedAccel.y = yIntersectedSide - entityCorners[i].y;
            }
            else
            {
                itteratedAccel.y = entAccel.y;
            }        
            itteratedAccel.x = entAccel.x;
        }
        /*makes sure the accel of the current itteration isnt more than the final accel*/
        if((itteratedAccel.x * xDirectionMultiplier) < (entAccel.x * xDirectionMultiplier))
        {
            entAccel.x = itteratedAccel.x;
        }
        if((itteratedAccel.y * yDirectionMultiplier) < (entAccel.y * yDirectionMultiplier))
        {
            entAccel.y = itteratedAccel.y;
        }
    };

    return(entAccel);
}
