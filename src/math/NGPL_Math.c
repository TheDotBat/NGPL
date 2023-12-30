#include "../../include/NGPL_Math.h"


// Functions
/*
 * Function: addVector
 * -------------------
 * Adds two Vector2F structures and returns the result.
 *
 * This function performs vector addition, combining two Vector2F structures
 * by adding their corresponding x and y coordinates.
 *
 * Parameters:
 *   v1: The first Vector2F to add.
 *   v2: The second Vector2F to add.
 *
 * Returns:
 *   Vector2F: The sum of the two vectors.
 */
Vector2F NGPL_AddVector(Vector2F v1, Vector2F v2) {
    Vector2F result = {v1.x + v2.x, v1.y + v2.y};
    return result;
}

/*
 * Function: multiplyVector
 * ------------------------
 * Multiplies a Vector2F by a scalar and returns the result.
 *
 * This function scales a Vector2F by multiplying both its x and y coordinates
 * by a given scalar value.
 *
 * Parameters:
 *   v: The Vector2F to be scaled.
 *   scalar: The scalar value to multiply the vector by.
 *
 * Returns:
 *   Vector2F: The scaled vector.
 */
Vector2F NGPL_MultiplyVector(Vector2F v, float scalar) {
    Vector2F result = {v.x * scalar, v.y * scalar};
    return result;
}

/*
 * Function: NGPL_GetMagnitude
 * ----------------------------
 * Calculates the magnitude of a vector given its x and y coordinates.
 *
 * x: x-coordinate of the vector
 * y: y-coordinate of the vector
 *
 * returns: Magnitude of the vector
 */
double NGPL_GetMagnitude(float x, float y)
{
    return sqrt(x*x+y*y);
}


