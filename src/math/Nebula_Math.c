#include "../../include/Nebula_Math.h"


// Functions
Vector2D addVector(Vector2D v1, Vector2D v2) {
    Vector2D result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

Vector2D multiplyVector(Vector2D v, float scalar) {
    Vector2D result = {v.x * scalar, v.y * scalar};
    return result;
}

/*
 * Function: getMagnitude
 * ----------------------------
 * Calculates the magnitude of a vector given its x and y coordinates.
 *
 * x: x-coordinate of the vector
 * y: y-coordinate of the vector
 *
 * returns: Magnitude of the vector
 */
double getMagnitude(float x, float y)
{
    return sqrt(x*x+y*y);
}


//NRect Nebula_CreateRect(float x, float y, int w, int h, int r, int g, int b, int a)
//{
//    NRect rect;
//    rect.x = x;
//    rect.y = y;
//    rect.w = w;
//    rect.h = h;
//    rect.color[0] = r;
//    rect.color[1] = g;
//    rect.color[2] = b;
//    rect.color[3] = a;
//    return rect;
//}
