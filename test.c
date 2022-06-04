#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameObjects.h"

int main()
{
    struct Vec2 entPos;
    entPos.x = 50;
    entPos.y = 50;

    struct Vec2 entSize;
    entSize.x = 32;
    entSize.y = 64;

    struct Vec2 entityCorners[4];
                entityCorners[0] = entPos;
                entityCorners[1] = (struct Vec2){.x = entPos.x, .y = entPos.y + entSize.y};
                entityCorners[2] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y};
                entityCorners[3] = (struct Vec2){.x = entPos.x + entSize.x, .y = entPos.y + entSize.y};

    for(int i = 0; i < 4; i++)
    {
        printf("x:%d\ny:%d\n", entityCorners[i].x, entityCorners[i].y);
    }

    return 0;
}