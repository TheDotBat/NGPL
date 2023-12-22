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

#ifndef NGPLG_PHYSICS_H
#define NGPLG_PHYSICS_H
#include "NGPLG.h"

typedef enum Collisions
{
    NONE = 0,
    TOP = 1 << 0,
    BOTTOM = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3,
}Collisions;

void NGPL_UpdateEntityX(NGPL_Entity* e, float deltaTime, float friction);

void NGPL_UpdateEntityY(NGPL_Entity* e, float deltaTime);

void NGPL_ApplyGravity(NGPL_Entity* e, float g);

void NGPL_Physics(NGPL_EntityPool* pool, float friction, float gravity, float deltaTime);

#endif