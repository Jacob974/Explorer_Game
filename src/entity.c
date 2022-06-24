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
    int xNearCollisionPoint;
    int xFarCollisionPoint;
    int yNearCollisionPoint;
    int yFarCollisionPoint;

    if(entAccel.x < 0)
    {
        xNearCollisionPoint = tilePos.x + tileSize.x;
        xFarCollisionPoint = tilePos.x;
    }
    else
    {
        xNearCollisionPoint = tilePos.x;
        xFarCollisionPoint = tilePos.x + tileSize.x;
    }
    if(entAccel.y < 0)
    {
        yNearCollisionPoint = tilePos.y + tileSize.y;
        yFarCollisionPoint = tilePos.y;
    }
    else
    {
        yNearCollisionPoint = tilePos.y;
        yFarCollisionPoint = tilePos.y + tileSize.y;
    }

    struct Vec2 entityCorners[4];
                entityCorners[0] = entPos;
                entityCorners[1] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y};
                entityCorners[2] = (struct Vec2){.x = entPos.x, .y = entPos.y + entSize.y};
                entityCorners[3] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y + entSize.y};
    
    for(int i = 0; i < 4; i++)
    {
        int xItteratedAccel = entAccel.x;
        int yItteratedAccel = entAccel.y;

        /* how far along each vector the sides of the tile intersect with the vector*/
        double xNearRatio = (double)(xNearCollisionPoint - entityCorners[i].x) / (double)(entAccel.x);
        double xFarRatio  = (double)(xFarCollisionPoint - entityCorners[i].x) / (double)(entAccel.x);
        double yNearRatio = (double)(yNearCollisionPoint - entityCorners[i].y) / (double)(entAccel.y);
        double yFarRatio  = (double)(yFarCollisionPoint - entityCorners[i].y) / (double)(entAccel.y);

        if((xNearRatio > yNearRatio) && (xNearRatio < yFarRatio) && (xNearRatio < 1.0) && (xNearRatio >= 0))//collides with verticle line
        {
            xItteratedAccel = xNearCollisionPoint - entityCorners[i].x;
        }
        else if((yNearRatio >= xNearRatio) && (yNearRatio < xFarRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0))//collides with horizontel line
        {
            yItteratedAccel = yNearCollisionPoint - entityCorners[i].y;
        }

        if(xItteratedAccel * entAccel.x < entAccel.x * entAccel.x)
        {
            entAccel.x = xItteratedAccel;
        }
        if(yItteratedAccel * entAccel.y < entAccel.y * entAccel.y)
        {
            entAccel.y = yItteratedAccel;
        }
    }
    printf("done\n");
    return entAccel;
}
