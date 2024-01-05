/*
  Nebula's Graphics Programming Library 
  2023-2023 Setoichi Yumaden <setoichi.dev@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef NDL_M_H
#define NDL_M_H
#include "NDL.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))



/*
 * Function: NDL_GetMagnitude
 * ----------------------------
 * Calculates the magnitude of a vector given its x and y coordinates.
 *
 * x: x-coordinate of the vector
 * y: y-coordinate of the vector
 *
 * returns: Magnitude of the vector
 */
double NDL_GetMagnitude(float x, float y);

/*
 * Function: NDL_AddVector
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
Vector2F NDL_AddVector(Vector2F v1, Vector2F v2);

/*
 * Function: NDL_MultiplyVector
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
Vector2F NDL_MultiplyVector(Vector2F v, float scalar);

#endif