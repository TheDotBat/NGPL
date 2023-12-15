#ifndef NMATH_H
#define NMATH_H

typedef struct Vector2D {
    float x;
    float y;
}Vector2D;

Vector2D addVector(Vector2D v1, Vector2D v2);

Vector2D multiplyVector(Vector2D v, float scalar);

typedef struct Object {
    Vector2D position;
    Vector2D size;
}Object;

typedef struct Collider2D {
    Vector2D position;
    Vector2D size;
}Collider2D;

#endif