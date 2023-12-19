#ifndef NGPL_MATH_H
#define NGPL_MATH_H
#include "NGPL.h"


// Structs


// Functions
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
double NGPL_GetMagnitude(float x, float y);

/*
 * Function: NGPL_AddVector
 * -------------------
 * Adds two Vector2D structures and returns the result.
 *
 * This function performs vector addition, combining two Vector2D structures
 * by adding their corresponding x and y coordinates.
 *
 * Parameters:
 *   v1: The first Vector2D to add.
 *   v2: The second Vector2D to add.
 *
 * Returns:
 *   Vector2D: The sum of the two vectors.
 */
Vector2D NGPL_AddVector(Vector2D v1, Vector2D v2);

/*
 * Function: NGPL_MultiplyVector
 * ------------------------
 * Multiplies a Vector2D by a scalar and returns the result.
 *
 * This function scales a Vector2D by multiplying both its x and y coordinates
 * by a given scalar value.
 *
 * Parameters:
 *   v: The Vector2D to be scaled.
 *   scalar: The scalar value to multiply the vector by.
 *
 * Returns:
 *   Vector2D: The scaled vector.
 */
Vector2D NGPL_MultiplyVector(Vector2D v, float scalar);

#endif