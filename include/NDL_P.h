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

#ifndef NDL_P_H
#define NDL_P_H
#include "NDL.h"


NDL_PhysicsGrid* NDL_CreatePhysicsGrid(int w, int h, int nRows, int nCols, int cellSize, int cellCapacity);

bool NDL_AABB_NegX(NDL_Entity* ent1, NDL_Entity* ent2);

bool NDL_AABB_PosX(NDL_Entity* ent1, NDL_Entity* ent2);

bool NDL_AABB_NegY(NDL_Entity* ent1, NDL_Entity* ent2);

bool NDL_AABB_PosY(NDL_Entity* ent1, NDL_Entity* ent2);

NDL_CollisionData NDL_GenerateCollisionInfo_P(NDL_Entity* ent1, NDL_Entity* ent2);

bool NDL_ObserveCollision_P(NDL_PhysicsGrid* grid);

void NDL_UpdateColliderComponent_P(NDL_ColliderComponent* collider, float deltaTime);

void NDL_CalcFrictionX_P(NDL_PhysicsSystem* phys, NDL_Entity* e);

void NDL_CalcFrictionY_P(NDL_PhysicsSystem* phys, NDL_Entity* e);

void NDL_HandleForces_P(NDL_Entity* e, NDL_PhysicsSystem* phys);

void NDL_HandlePositions_P(NDL_PhysicsSystem* phys, NDL_Entity* e, float deltaTime, int UPF);

NDL_PhysicsSystem* NDL_CreatePhysicsSystem(int gridSpaceW, int gridSpaceH, int nRows, int nCols, int gridSpaceCellSize, int gridSpaceCellCapacity);

void NDL_AddEntityToGrid(NDL_Entity* e, NDL_PhysicsGrid* grid);

#endif