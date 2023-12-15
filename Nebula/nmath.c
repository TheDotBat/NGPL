#include "nmath.h"


Vector2D addVector(Vector2D v1, Vector2D v2) {
    Vector2D result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

Vector2D multiplyVector(Vector2D v, float scalar) {
    Vector2D result = {v.x * scalar, v.y * scalar};
    return result;
}

