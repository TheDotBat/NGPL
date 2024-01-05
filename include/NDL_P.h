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


PhysicsGrid* CreatePhysicsGrid(int w, int h, int nRows, int nCols, int cellSize, int cellCapacity);

bool AABB_NegX(NDL_Entity* ent1, NDL_Entity* ent2);

bool AABB_PosX(NDL_Entity* ent1, NDL_Entity* ent2);

bool AABB_NegY(NDL_Entity* ent1, NDL_Entity* ent2);

bool AABB_PosY(NDL_Entity* ent1, NDL_Entity* ent2);

CollisionData GenerateCollisionInfo_P(NDL_Entity* ent1, NDL_Entity* ent2);

bool ObserveCollision_P(PhysicsGrid* grid);

void UpdateColliderComponent_P(ColliderComponent* collider, float deltaTime);

void CalcFrictionX_P(PhysicsSystem* phys, NDL_Entity* e);

void CalcFrictionY_P(PhysicsSystem* phys, NDL_Entity* e);

void HandleForces_P(NDL_Entity* e, PhysicsSystem* phys);

void HandlePositionsColliderComponent_P(PhysicsSystem* phys, NDL_Entity* e, float deltaTime, int UPF);

PhysicsSystem* CreatePhysicsSystem(int gridSpaceW, int gridSpaceH, int nRows, int nCols, int gridSpaceCellSize, int gridSpaceCellCapacity);

void AddEntityToGrid(NDL_Entity* e, PhysicsGrid* grid);

#endif