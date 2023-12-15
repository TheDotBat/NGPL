#include "common.h"

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



