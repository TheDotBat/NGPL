#ifndef NEBULA_MATH_H
#define NEBULA_MATH_H

#include "Nebula.h"

// Types
typedef SDL_Rect Rect;

// Structs
typedef struct Vector2D {
    float x;
    float y;
}Vector2D;

typedef struct Object {
    Vector2D position;
    Vector2D size;
}Object;

typedef struct Collider2D {
    Vector2D position;
    Vector2D size;
}Collider2D;

typedef struct NRect
{
    float x,y;
    int w,h;
    int color[4];
} NRect;

// Functions
double getMagnitude(float x, float y);
Vector2D addVector(Vector2D v1, Vector2D v2);
Vector2D multiplyVector(Vector2D v, float scalar);

#endif