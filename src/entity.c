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
    //
    //
    /* this function is based off of a tutorial from Javidx9, the video is https://www.youtube.com/watch?v=8JJ-4JgR7Dg */
    //
    //

    struct Vec2 entityCollisionPoint = (struct Vec2){.x = entPos.x + entSize.x / 2, .y = entPos.y + entSize.y / 2}; //the center of the entity with the smaller rounded side to the left or the top

    int xNearCollisionPoint;
    int xFarCollisionPoint;
    int yNearCollisionPoint;
    int yFarCollisionPoint;

    if(entAccel.x < 0)
    {
        xNearCollisionPoint = tilePos.x + tileSize.x + (entSize.x / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
        xFarCollisionPoint = tilePos.x - entSize.x + (entSize.x / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
    }
    else
    {
        xNearCollisionPoint = tilePos.x - entSize.x + (entSize.x / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
        xFarCollisionPoint = tilePos.x + tileSize.x + (entSize.x / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
    }
    if(entAccel.y < 0)
    {
        yNearCollisionPoint = tilePos.y + tileSize.y + (entSize.y / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
        yFarCollisionPoint = tilePos.y - entSize.y + (entSize.y / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
    }
    else
    {
        yNearCollisionPoint = tilePos.y - entSize.y + (entSize.y / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
        yFarCollisionPoint = tilePos.y + tileSize.y + (entSize.y / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
    }

    /* how far along each vector the sides of the tile intersect with the vector*/
    double xNearRatio = (double)(xNearCollisionPoint - entityCollisionPoint.x) / (double)(entAccel.x);
    double xFarRatio  = (double)(xFarCollisionPoint - entityCollisionPoint.x) / (double)(entAccel.x);
    double yNearRatio = (double)(yNearCollisionPoint - entityCollisionPoint.y) / (double)(entAccel.y);
    double yFarRatio  = (double)(yFarCollisionPoint - entityCollisionPoint.y) / (double)(entAccel.y);

    if((xNearRatio > yNearRatio) && (xNearRatio < yFarRatio) && (xNearRatio < 1.0) && (xNearRatio >= 0))//collides with verticle line
    {
        entAccel.x = xNearCollisionPoint - entityCollisionPoint.x;
    }
    else if((yNearRatio > xNearRatio) && (yNearRatio < xFarRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0))//collides with horizontel line
    {
        entAccel.y = yNearCollisionPoint - entityCollisionPoint.y;
    }
    else if((xNearRatio == yNearRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0)) //this is an edge case, might fix it at some point
    {
        entAccel.x = xNearCollisionPoint - entityCollisionPoint.x;
        entAccel.y = yNearCollisionPoint - entityCollisionPoint.y;
    }


    printf("done\n");
    return entAccel;
}
