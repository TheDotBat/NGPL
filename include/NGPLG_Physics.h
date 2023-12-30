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




NGPL_RigidBody* NGPL_CreateRigidBody(PSpace* space, bool isTopDown, float x, float y, int w, int h);

void NGPL_UpdateRigidBody(NGPL_RigidBody* rb, float deltaTime);

void NGPL_BlitRigidBody(Renderer ren, NGPL_RigidBody* rb, NGPL_Color color);

void NGPL_SetRigidBodyMass(NGPL_RigidBody* rb, float nMass);

void NGPL_SetRigidBodyDynamic(NGPL_RigidBody* rb, bool isDynamic);

void NGPL_InitPSpace(PSpace* space, int cellSize, int nRows, int nCols);

PSpace NGPL_CreatePhysicsSpace(int cellSize, int nRows, int nCols, int gridX, int gridY);

void NGPL_PGCalcFrictionX(PSpace* space, NGPL_RigidBody* rb);

void NGPL_PGCalcFrictionY(PSpace* space, NGPL_RigidBody* rb);

void NGPL_ApplyForces(PSpace* space, NGPL_RigidBody* rb);

void NGPL_SetPhysicsSpaceGravity(PSpace* space, float g);

void NGPL_SetPhysicsSpaceFriction(PSpace* space, float f);

void NGPL_GetOccupiedCells(PSpace *space, NGPL_RigidBody *rb, int *startRow, int *endRow, int *startCol, int *endCol);

void NGPL_PSpaceAddEntity(PSpace *space, NGPL_RigidBody *rb);

void NGPL_PSpaceRemEntity(PSpace* space, NGPL_RigidBody* rb);

void NGPL_PSpaceShowGrid(Renderer ren, PSpace* space, NGPL_Color gridColor);

void NGPL_PSpaceFree(PSpace* space);

bool NGPL_NegXAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_PosXAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_NegYAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

bool NGPL_PosYAABB(NGPL_RigidBody* rb1, NGPL_RigidBody* rb2);

CollisionInfo NGPL_CollisionInfoCheck(NGPL_RigidBody* dynamicEntity, NGPL_RigidBody* staticEntity);

NGPL_RigidBody* NGPL_GetDynamicEntityFromCollisionInfo(CollisionInfo collision);

NGPL_RigidBody* NGPL_GetStaticEntityFromCollisionInfo(CollisionInfo collision);

void NGPL_ResolveCollision(PSpace* space, CollisionInfo collision, float deltaTime);

bool NGPL_PSpaceObserve(PSpace* space, float deltaTime);

void NGPL_PSpaceUpdateBodies(PSpace* space, NGPL_RigidBody* rb, float deltaTime, int CCD_Step);

void NGPL_CreateEntityRigidBody(PSpace* space, bool isTopDown, NGPL_Entity* e, float mass, Vector2F position, Vector2 size);

void NGPL_EntityUpdate(NGPL_Entity* e);

#endif