#include "entity.h"
#include <math.h>
#include <stdio.h>

Entity createEntity(int xCoord, int yCoord, int x, int y, int w, int h, const char *filepath, SDL_Renderer *renderer)
{
    Entity temp;
    temp.dest.x = x;
    temp.dest.y = y;
    temp.dest.w = w;
    temp.dest.h = h;

    temp.coords.x = xCoord;
    temp.coords.y = yCoord;

    temp.accel.x = 0;
    temp.accel.y = 0;
    temp.texture = IMG_LoadTexture(renderer, filepath);

    return temp;
}
void digTile(TileMap* tileMap, Entity* entity, Vec2 endOfSelection)
{
}
void detectCollisionPoint(Entity* entity, TileMap* tileMap)
{
    // this function is based off of a tutorial from Javidx9, the video is https://www.youtube.com/watch?v=8JJ-4JgR7Dg

    Vec2 entityCollisionPoint = (Vec2){.x = entity->coords.x + entity->dest.w / 2, .y = entity->coords.y + entity->dest.h / 2}; //the center of the entity with the smaller rounded side to the left or the top

    int xNearCollisionPoint;
    int xFarCollisionPoint;
    int yNearCollisionPoint;
    int yFarCollisionPoint;

    Tile** laterSortedTiles = malloc(1); //tiles that will be sorted after all the other tiles because the entity hits the corner of the tile
    int laterSortedTilesSize = 0;

    for(int i = 0; i < tileMap->tileHight * tileMap->tileWidth; i++) //itterates through all the tils and decreases the entity's acceleration if it hits a block
    {
        if((tileMap->tileList[i].exists == 1) && (tileMap->tileList[i].collidable == 1)) //checks if the the tile exists
        {
            Vec2 collisionPoint = detectTileCollision(tileMap->tileList[i].coords, (Vec2){.x = 32, .y = 32}, entity->coords, (Vec2){.x = entity->dest.w, .y = entity->dest.h}, entity->accel);
            
            if((abs(collisionPoint.y) <= abs(entity->accel.y)) && (abs(collisionPoint.x) <= abs(entity->accel.x)))
            {
                //adds it to a list for later collision detection
                laterSortedTilesSize++;
                laterSortedTiles = realloc(laterSortedTiles, sizeof(Tile*) * laterSortedTilesSize);
                laterSortedTiles[laterSortedTilesSize - 1] = &tileMap->tileList[i];
            }
            else if(abs(entity->accel.y) > abs(collisionPoint.y))
            {
                entity->accel.y = collisionPoint.y;
            }
            else if(abs(entity->accel.x) > abs(collisionPoint.x))
            {
                entity->accel.x = collisionPoint.x;
            }
        }
    }
    for(int i = 0; i < laterSortedTilesSize; i++)
    {
        //yeah i know im copying and pasting code, Ill prob deal with it later
        if(entity->accel.x < 0)
        {
            xNearCollisionPoint = laterSortedTiles[i]->coords.x * 32 + 32 + (entity->dest.w / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
            xFarCollisionPoint = laterSortedTiles[i]->coords.x * 32 - entity->dest.w + (entity->dest.w / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
        }
        else
        {
            xNearCollisionPoint = laterSortedTiles[i]->coords.x * 32 - entity->dest.w + (entity->dest.w / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
            xFarCollisionPoint = laterSortedTiles[i]->coords.x * 32 + 32 + (entity->dest.w / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
        }
        if(entity->accel.y < 0)
        {
            yNearCollisionPoint = laterSortedTiles[i]->coords.y * 32 + 32 + (entity->dest.h / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
            yFarCollisionPoint = laterSortedTiles[i]->coords.y * 32 - entity->dest.h + (entity->dest.h / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
        }
        else
        {
            yNearCollisionPoint = laterSortedTiles[i]->coords.y * 32 - entity->dest.h + (entity->dest.h / 2); //half the entity's length is added rounded up to compensate for the collion detection happening in the center of the entity
            yFarCollisionPoint = laterSortedTiles[i]->coords.y * 32 + 32 + (entity->dest.h / 2); //half the entity's length is subtracted rounded down to compensate for the collion detection happening in the center of the entity
        }

        /* how far along each vector the sides of the tile intersect with the vector*/
        double xNearRatio = (double)(xNearCollisionPoint - entityCollisionPoint.x) / (double)(entity->accel.x);
        double xFarRatio  = (double)(xFarCollisionPoint - entityCollisionPoint.x) / (double)(entity->accel.x);
        double yNearRatio = (double)(yNearCollisionPoint - entityCollisionPoint.y) / (double)(entity->accel.y);
        double yFarRatio  = (double)(yFarCollisionPoint - entityCollisionPoint.y) / (double)(entity->accel.y);

        if((xNearRatio > yNearRatio) && (xNearRatio < yFarRatio) && (xNearRatio < 1.0) && (xNearRatio >= 0))//collides with verticle line
        {
            entity->accel.x = xNearCollisionPoint - entityCollisionPoint.x;
        }
        else if((yNearRatio > xNearRatio) && (yNearRatio < xFarRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0))//collides with horizontel line
        {
            entity->accel.y = yNearCollisionPoint - entityCollisionPoint.y;
        }
        else if((xNearRatio == yNearRatio) && (yNearRatio < 1.0) && (yNearRatio >= 0)) //this is an edge case, might fix it at some point
        {
            entity->accel.y = yNearCollisionPoint - entityCollisionPoint.y;
        }
    }
    free(laterSortedTiles);
}
