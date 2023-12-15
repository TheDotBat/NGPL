#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "../SDL2/include/SDL.h"


// CONSTANTS
typedef SDL_Rect Rect;

typedef struct Vector2
{
    float x,y;
} Vector2;

typedef struct NRect
{
    float x,y;
    int w,h;
    int color[4];
} NRect;




#endif