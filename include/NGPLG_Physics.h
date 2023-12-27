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


typedef struct Edge
{
 Vector2D V1;
 Vector2D V2;
}Edge;

typedef struct NGPL_Rect
{
    float x;
    float y;
    int w;
    int h;
    Edge left;
    Edge top;
    Edge right;
    Edge bottom;
}NGPL_Rect;

typedef struct RigidBody
{
    const char* tag;
    bool isDynamic;
    bool isStatic;
    float mass;
    Vector2D position;
    Vector2D velocity;
    NGPL_Rect r;
    int cRow,cCol;
}RigidBody;

typedef struct PGridCell
{
    RigidBody** entities;
    int entityCount;
}PGridCell;

typedef enum COLLISION_TYPES
{
    L,
    R,
    U,
    D,
    None
}COLLISION_TYPES;

typedef struct CollisionInfo
{
    bool none;
    RigidBody* dE;
    RigidBody* sE;
    Vector2D point;  // Collision point
    float massDynamic;
    float massStatic;
    Vector2D velocityDynamic;
    COLLISION_TYPES typeX;
    COLLISION_TYPES typeY;
}CollisionInfo;

typedef struct PSpace
{
    float g;
    float f;
    int cellSize;
    int rows;
    int cols;
    Rect bounds;
    PGridCell** cells;
}PSpace;

void NGPL_DrawEdge(Renderer ren, Edge* edge);

NGPL_Rect NGPL_CreateRect(int w, int h, float x, float y);

void NGPL_UpdateRect(NGPL_Rect* r);

void NGPL_BlitRect2(Renderer ren, NGPL_Rect* r);

RigidBody CreateRigidBody(float x, float y, int w , int h);

void NGPL_UpdateRigidBody(RigidBody* rb, float deltaTime);

void NGPL_BlitRigidBody(Renderer ren, RigidBody* rb);

void NGPL_SetRigidBodyMass(RigidBody* rb, float nMass);

void NGPL_SetRigidBodyDynamic(RigidBody* rb, bool isDynamic);

void NGPL_InitPSpace(PSpace* space, int cellSize, int nRows, int nCols);

PSpace NGPL_CreatePhysicsSpace(int cellSize, int nRows, int nCols, int gridX, int gridY);

void NGPL_PGCalcFriction(PSpace* space, RigidBody* rb);

void ApplyForces(PSpace* space, RigidBody* rb);

void NGPL_SetPhysicsSpaceGravity(PSpace* space, float g);

void NGPL_SetPhysicsSpaceFriction(PSpace* space, float f);

void NGPL_GetOccupiedCells(PSpace *space, RigidBody *rb, int *startRow, int *endRow, int *startCol, int *endCol);

void NGPL_PSpaceAddEntity(PSpace *space, RigidBody *rb);

void NGPL_PSpaceRemEntity(PSpace* space, RigidBody* rb);

void NGPL_PSpaceShowGrid(Renderer ren, PSpace* space, NGPL_Color gridColor);

void NGPL_PSpaceFree(PSpace* space);

bool NGPL_NegXAABB(RigidBody* rb1, RigidBody* rb2);

bool NGPL_PosXAABB(RigidBody* rb1, RigidBody* rb2);

bool NGPL_NegYAABB(RigidBody* rb1, RigidBody* rb2);

bool NGPL_PosYAABB(RigidBody* rb1, RigidBody* rb2);

CollisionInfo NGPL_CollisionInfoCheck(RigidBody* dynamicEntity, RigidBody* staticEntity);

RigidBody* GetDynamicEntityFromCollisionInfo(CollisionInfo collision);

RigidBody* GetStaticEntityFromCollisionInfo(CollisionInfo collision);

void NGPL_ResolveCollision(PSpace* space, CollisionInfo collision, float deltaTime);

bool NGPL_PSpaceObserve(PSpace* space, float deltaTime);

void NGPL_PSpaceEntityUpdate(PSpace* space, RigidBody* rb, float deltaTime, int CCD_Step, Renderer ren);

#endif