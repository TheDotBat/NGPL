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




NGPL_RigidBody* NGPL_CreateRigidBody(NGPL_PSpace* space, bool isTopDown, float x, float y, int w, int h);

void NGPL_UpdateRigidBody(NGPL_RigidBody* rb, float deltaTime);

void NGPL_SetRigidBodyMass(NGPL_RigidBody* rb, float nMass);

void NGPL_SetRigidBodyDynamic(NGPL_RigidBody* rb, bool isDynamic);

void NGPL_InitPSpace(NGPL_PSpace* space, int cellSize, int nRows, int nCols);

NGPL_PSpace NGPL_CreatePhysicsSpace(int cellSize, int nRows, int nCols, int gridX, int gridY);

void NGPL_PGCalcFrictionX(NGPL_PSpace* space, NGPL_RigidBody* rb);

void NGPL_PGCalcFrictionY(NGPL_PSpace* space, NGPL_RigidBody* rb);

void NGPL_ApplyForces(NGPL_PSpace* space, NGPL_RigidBody* rb);

void NGPL_SetPhysicsSpaceGravity(NGPL_PSpace* space, float g);

void NGPL_SetPhysicsSpaceFriction(NGPL_PSpace* space, float f);

void NGPL_GetOccupiedCells(NGPL_PSpace *space, NGPL_RigidBody *rb, int *startRow, int *endRow, int *startCol, int *endCol);

void NGPL_PSpaceAddEntity(NGPL_PSpace *space, NGPL_RigidBody *rb);

void NGPL_PSpaceRemEntity(NGPL_PSpace* space, NGPL_RigidBody* rb);

void NGPL_PSpaceFree(NGPL_PSpace* space);

bool NGPL_NegXAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_PosXAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_NegYAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_PosYAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

CollisionInfo NGPL_CollisionInfoCheck(NGPL_RigidBody* dynamicEntity, NGPL_RigidBody* staticEntity);

NGPL_RigidBody* NGPL_GetDynamicEntityFromCollisionInfo(CollisionInfo collision);

NGPL_RigidBody* NGPL_GetStaticEntityFromCollisionInfo(CollisionInfo collision);

void NGPL_ResolveCollision(NGPL_PSpace* space, CollisionInfo collision, float deltaTime);

bool NGPL_PSpaceObserve(NGPL_PSpace* space, float deltaTime);

void NGPL_PSpaceUpdateBodies(NGPL_PSpace* space, NGPL_RigidBody* rb, float deltaTime, int CCD_Step);

void NGPL_CreateEntityRigidBody(NGPL_PSpace* space, bool isTopDown, NGPL_Entity* e, float mass, Vector2F position, Vector2 size);

void NGPL_PSpaceUpdate(NGPL_PSpace* space, float deltaTime, int CCD_Step);

#endif