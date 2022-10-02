#include "utils.h"

Vec2 detectTileCollision(Vec2 staticTilePos, Vec2 staticTileSize, Vec2 dynamicTilePos, Vec2 dynamicTileSize, Vec2 amountMoved)
{
    Vec2 dynamicTileCollisionPoint = (Vec2){.x = dynamicTilePos.x + dynamicTileSize.x / 2, .y = dynamicTilePos.y + dynamicTileSize.y / 2}; //the center of the entity with the smaller rounded side to the left or the top

    int xNearCollisionPoint;
    int xFarCollisionPoint;
    int yNearCollisionPoint;
    int yFarCollisionPoint;

    if(amountMoved.x < 0)
    {
        xNearCollisionPoint = staticTilePos.x * 32 + 32 + (dynamicTileSize.x / 2);
        xFarCollisionPoint = staticTilePos.x * 32 - dynamicTilePos.x + (dynamicTilePos.x / 2);
    }
    else
    {
        xNearCollisionPoint = staticTilePos.x * 32 - dynamicTilePos.x + (dynamicTilePos.x / 2);
        xFarCollisionPoint = staticTilePos.x * 32 + 32 + (dynamicTileSize.x / 2);
    }
    if(amountMoved.y < 0)
    {
        yNearCollisionPoint = staticTilePos.y * 32 + 32 + (dynamicTileSize.y / 2);
        yFarCollisionPoint = staticTilePos.y * 32 - dynamicTilePos.y + (dynamicTilePos.y / 2);
    }
    else
    {
        yNearCollisionPoint = staticTilePos.y * 32 - dynamicTilePos.y + (dynamicTilePos.y / 2);
        yFarCollisionPoint = staticTilePos.y * 32 + 32 + (dynamicTileSize.y / 2);
    }

    double xNearRatio = (double)(xNearCollisionPoint - dynamicTileCollisionPoint.x) / (double)(amountMoved.x);
    double xFarRatio  = (double)(xFarCollisionPoint - dynamicTileCollisionPoint.x) / (double)(amountMoved.x);
    double yNearRatio = (double)(yNearCollisionPoint - dynamicTileCollisionPoint.y) / (double)(amountMoved.y);
    double yFarRatio  = (double)(yFarCollisionPoint - dynamicTileCollisionPoint.y) / (double)(amountMoved.y);


    if((xNearRatio >= yNearRatio) && (xNearRatio < yFarRatio) && (xNearRatio < 1.0) && (xNearRatio >= 0))
    {
        amountMoved.x = xNearCollisionPoint - dynamicTileCollisionPoint.x; //adjusts the x accel
    }
    if((yNearRatio >= xNearRatio) && (yNearRatio < xFarRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0))
    {
        amountMoved.y = yNearCollisionPoint - dynamicTileCollisionPoint.y; //adjusts the y accel
    }

    return(amountMoved);
}