#include "../../include/NDL_P.h"


NDL_PhysicsGrid* NDL_CreatePhysicsGrid(int w, int h, int nRows, int nCols, int cellSize, int cellCapacity)
{
    NDL_PhysicsGrid* pGrid = malloc(sizeof(NDL_PhysicsGrid));
    pGrid->w = w;
    pGrid->h = h;
    pGrid->r = nRows;
    pGrid->c = nCols;
    pGrid->cellSize = cellSize;

    pGrid->cells = malloc(sizeof(Cell*)*pGrid->r);
    for (int i = 0; i < pGrid->r; ++i)
    {
        pGrid->cells[i] = malloc(sizeof(Cell)*pGrid->c);
        for (int j = 0; j < pGrid->c; ++j)
        {
            pGrid->cells[i][j].pool = NDL_CreatePool(cellCapacity);
        }
    }
    
    return pGrid;
}

bool NDL_AABB_NegX(NDL_Entity* ent1, NDL_Entity* ent2)
{
    NDL_ColliderComponent* collider1 = ent1->collider;
    NDL_ColliderComponent* collider2 = ent2->collider;
    if ((int)collider1->r.left.V1.x == (int)collider2->r.right.V1.x & (collider1->r.left.V1.y <= collider2->r.right.V2.y & collider1->r.left.V2.y >= collider2->r.right.V1.y))
    {
        collider1->position.x = collider2->r.x + collider2->r.w+0.1; // Position collider1 to the right of collider2
        collider1->velocity.x = 0.0;
        return true;
    }
    return false;
}

bool NDL_AABB_PosX(NDL_Entity* ent1, NDL_Entity* ent2)
{
    NDL_ColliderComponent* collider1 = ent1->collider;
    NDL_ColliderComponent* collider2 = ent2->collider;
    if ((int)collider1->r.right.V1.x == (int)collider2->r.left.V1.x & (collider1->r.right.V1.y <= collider2->r.left.V2.y & collider1->r.right.V2.y >= collider2->r.left.V1.y))
    {
        collider1->position.x = collider2->r.x - collider1->r.w-0.1; // Position collider1 to the left of collider2
        collider1->velocity.x = 0.0;
        return true;
    }
    return false;
}

bool NDL_AABB_NegY(NDL_Entity* ent1, NDL_Entity* ent2)
{
    NDL_ColliderComponent* collider1 = ent1->collider;
    NDL_ColliderComponent* collider2 = ent2->collider;
    if ((int)collider1->r.top.V1.y == (int)collider2->r.bottom.V1.y & (collider1->r.top.V1.x < collider2->r.bottom.V2.x & collider1->r.top.V2.x > collider2->r.bottom.V1.x))
    {
        collider1->position.y = collider2->r.y + collider2->r.h+0.1;
        collider1->velocity.y = 0.0;
        ent1->velocity.y = 0.0;
        return true;
    }
    return false;
}

bool NDL_AABB_PosY(NDL_Entity* ent1, NDL_Entity* ent2)
{
    NDL_ColliderComponent* collider1 = ent1->collider;
    NDL_ColliderComponent* collider2 = ent2->collider;
    if ((int)collider1->r.bottom.V1.y == (int)collider2->r.top.V1.y & (collider1->r.bottom.V1.x < collider2->r.top.V2.x & collider1->r.bottom.V2.x > collider2->r.top.V1.x))
    {
        collider1->position.y = collider2->r.y - collider1->r.h-0.1; // Position collider1 to the right of collider2
        collider1->velocity.y = 0.0;
        ent1->velocity.y = 0.0;
        return true;
    }
    return false;
}

NDL_CollisionData NDL_GenerateCollisionInfo_P(NDL_Entity* ent1, NDL_Entity* ent2)
{
    NDL_CollisionData info;
    info.none = true; // No collision detected yet

    // Perform AABB collision check
    bool isCollisionX;
    bool isCollisionY;

    NDL_ColliderComponent* collider1 = ent1->collider;
    NDL_ColliderComponent* collider2 = ent2->collider;

    if (collider1->velocity.x < 0.0)
    {
        info._typeX = L;
        isCollisionX = NDL_AABB_NegX(ent1, ent2);
    } else if (collider1->velocity.x > 0.0) {
        info._typeX = R;
        isCollisionX = NDL_AABB_PosX(ent1, ent2);
    } else {
        info._typeX = None;
        isCollisionX = false;
    }
    
    if (collider1->velocity.y < 0.0)
    {
        info._typeY = U;
        isCollisionY = NDL_AABB_NegY(ent1, ent2);
    } else if (collider1->velocity.y > 0.0) {
        info._typeY = D;
        isCollisionY = NDL_AABB_PosY(ent1, ent2);
    } else {
        info._typeY = None;
        isCollisionY = false;
    }

    if (isCollisionX || isCollisionY)
    {
        // Collision detected, calculate collision point
        info.none = false;
        info._point.x = (max(collider1->r.left.V1.x, collider2->r.left.V1.x) + min(collider1->r.right.V1.x, collider2->r.right.V1.x)) / 2;
        info._point.y = (max(collider1->r.top.V1.y, collider2->r.top.V1.y) + min(collider1->r.bottom.V1.y, collider2->r.bottom.V1.y)) / 2;
    }

    // Populate other collision details
    info._for = collider1;
    info._against = collider2;
    info._massFor = collider1->mass;
    info._massAgainst = collider2->mass;
    info._velocityFor = collider1->velocity;

    return info;
}

bool NDL_ObserveCollision_P(NDL_PhysicsGrid* grid)
{
    bool collisionDetected = false;
    // Iterate through entities in the cell
    for (int row = 0; row < grid->r; ++row)   // rows
    {
        for (int col = 0; col < grid->c; ++col)   // cols
        {
            NDL_Pool* cell = grid->cells[row][col].pool;
            for (int i = 0; i < cell->size; ++i)
            {
                NDL_Entity* entityA = cell->entities[i];
                // Check for collision with other entities in the cell
                for (int j = 0; j < cell->size; ++j)
                {
                    if (i == j) continue;
                    NDL_Entity* entityB = cell->entities[j];
                    // Apply collision rules between entityA and entityB
                    NDL_CollisionData collision = NDL_GenerateCollisionInfo_P(entityA, entityB);
                    if (!collision.none)
                    {
                        //printf("collision data generated!\n1st step AABB resolution calculated!\n");
                        collisionDetected = true;
                    }
                }
            }    
        }
    }
    return collisionDetected;
}

void NDL_UpdateColliderComponent_P(NDL_ColliderComponent* collider, float deltaTime)
{
    collider->position.x += collider->velocity.x * deltaTime;
    collider->position.y += collider->velocity.y * deltaTime;
    collider->r.x = collider->position.x;
    collider->r.y = collider->position.y;
    NDL_UpdateRect(&collider->r);
}

void NDL_CalcFrictionX_P(NDL_PhysicsSystem* phys, NDL_Entity* e)
{
    if (e->velocity.x > 0)
    {
        e->velocity.x -= phys->friction.x;
        if (e->velocity.x < 0)
        {
            e->velocity.x = 0;
        }
    } else if (e->velocity.x < 0) {
        e->velocity.x += phys->friction.x;
        if (e->velocity.x > 0)
        {
            e->velocity.x = 0;
        }
    }
}

void NDL_CalcFrictionY_P(NDL_PhysicsSystem* phys, NDL_Entity* e)
{
    if (e->velocity.y > 0) {
        e->velocity.y -= phys->friction.y;
        if (e->velocity.y < 0) {
            e->velocity.y = 0;
        }
    } else if (e->velocity.y < 0) {
        e->velocity.y += phys->friction.y;
        if (e->velocity.y > 0) {
            e->velocity.y = 0;
        }
    }
}

void NDL_HandleForces_P(NDL_Entity* e, NDL_PhysicsSystem* phys)
{
    NDL_ColliderComponent* collider = e->collider;
    e->velocity.y += phys->gravity;
    float gf = (phys->gravity*collider->mass/20.0)*((collider->mass*10)/(collider->mass*10));
    collider->isDynamic ? collider->velocity.y += gf : 0;
    phys->frictionX & e->isDynamic ? NDL_CalcFrictionX_P(phys, e) : NULL;
    phys->frictionY & e->isDynamic ? NDL_CalcFrictionY_P(phys, e) : NULL;
}

void NDL_HandlePositions_P(NDL_PhysicsSystem* phys, NDL_Entity* e, float deltaTime, int UPF)
{
    int STEPS_FOR_CCD = UPF > 0 ? UPF : 100;
    float stepDelta = deltaTime / STEPS_FOR_CCD;

    for (int step = 0; step < STEPS_FOR_CCD; ++step) {

        if (NDL_HasComponent(e, COLLIDER_COMPONENT))
        {
            // Update NDL_Entity position
            NDL_UpdateColliderComponent_P(e->collider, stepDelta);
            e->position.x = e->collider->position.x;
            e->position.y = e->collider->position.y;
            NDL_UpdateRect(&e->collider->r);  // Update the collider/rectangle after adjusting the position
            
            e->sprite->imageRect.x = e->collider->position.x;
            e->sprite->imageRect.y = e->collider->position.y;

            phys->handleCollisions(phys->gridSpace);
        }else {
            e->position.x += e->velocity.x * deltaTime;
            e->position.y += e->velocity.y * deltaTime;
            e->sprite->imageRect.x = e->position.x;
            e->sprite->imageRect.y = e->position.y;
        }
    }
}

NDL_PhysicsSystem* NDL_CreatePhysicsSystem(int gridSpaceW, int gridSpaceH, int nRows, int nCols, int gridSpaceCellSize, int gridSpaceCellCapacity)
{
    NDL_PhysicsSystem* p = malloc(sizeof(NDL_PhysicsSystem));
    p->gravity = 9.8;
    p->friction.x = 0.98;
    p->friction.y = 0.98;
    p->frictionX = true;
    p->frictionY = false;
    p->forTopDown = false;
    p->gridSpace = NDL_CreatePhysicsGrid(gridSpaceW,gridSpaceH, nRows, nCols, gridSpaceCellSize, gridSpaceCellCapacity);
    p->handleForces = NDL_HandleForces_P;
    p->handlePositions = NDL_HandlePositions_P;
    p->handleCollisions = NDL_ObserveCollision_P;
    return p;
}

void NDL_AddEntityToGrid(NDL_Entity* e, NDL_PhysicsGrid* grid)
{
    // Calculate grid cell based on entity position
    int cellX = e->position.x / grid->cellSize;
    int cellY = e->position.y / grid->cellSize;

    // Check if the calculated cell is within grid bounds
    if (cellX >= 0 && cellX < grid->c && cellY >= 0 && cellY < grid->r) {
        NDL_AddToPool(e, grid->cells[cellX][cellY].pool);
    } else {
        printf("NDL_Entity position is out of grid bounds!\n");
    }
}