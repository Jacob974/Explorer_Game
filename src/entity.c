#include "entity.h"
#include <math.h>

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
struct Vec2 detectCollisionPoint(struct Vec2 entAccel, struct Vec2 entPos, struct Vec2 tilePos, struct Vec2 tileSize)
{
    struct Vec2 collisionPoint;
    
    /* How far along the vector each side is. The sides are represented as their . 
    These equations return the position of the specific point of the tile minus the coordinate of the entity.
    The number is then divided by the acceleration amount for that side.
    If the accel is 0, the whole number is turned into 0 since you cant divide by 0 normally*/

 
    double leftXRatio = ((double)(tilePos.x - entPos.x) / (double)(entAccel.x));
    double rightXRatio = ((double)(tilePos.x + tileSize.x - entPos.x) / (double)(entAccel.x));
    double topYRatio = ((double)(tilePos.y - entPos.y) / (double)(entAccel.y));
    double bottomYRatio = ((double)(tilePos.y + tileSize.y - entPos.y) / (double)(entAccel.y));

    /* Which side of the tile the line intersects. This is based on whether the accel is negetive or not */
    int XIntersectedSide = (entAccel.x < 0 ? tilePos.x + tileSize.x : tilePos.x); //right/left
    int YIntersectedSide = (entAccel.y < 0 ? tilePos.y + tileSize.y : tilePos.y); //bottom/top

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
            collisionPoint.x = XIntersectedSide;
            collisionPoint.y = entPos.y + (nearXRatio * entAccel.y);
        }
        else
        {
            collisionPoint.x = entPos.x + entAccel.x;
            collisionPoint.y = entPos.y + entAccel.y;
        }
    }
    else //hits the vertical line
    {
        
        if((nearYRatio < 1.0) && (nearYRatio < farXRatio) && (nearYRatio >= 0))//detects if theres actually a collision
        {
            collisionPoint.y = YIntersectedSide;
            collisionPoint.x = entPos.x + (nearYRatio * entAccel.x);
        }
        else
        {
            collisionPoint.x = entPos.x + entAccel.x;
            collisionPoint.y = entPos.y + entAccel.y;
        }        
    }
    return(collisionPoint);
}
