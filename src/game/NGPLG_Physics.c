#include "../../include/NGPLG_Physics.h"


void NGPL_DrawEdge(Renderer ren, Edge* edge)
{
    SDL_SetRenderDrawColor(ren, 100,100,255,255);
    SDL_RenderDrawLineF(ren, edge->V1.x, edge->V1.y, edge->V2.x, edge->V2.y);
}

NGPL_Rect NGPL_CreateRect(int w, int h, float x, float y)
{
    NGPL_Rect r;
    
    r.x = x;
    r.y = y;

    r.w = w;
    r.h = h;

    Edge left = {{r.x, r.y}, {r.x, r.y+r.h}};
    Edge top = {{r.x, r.y}, {r.x+r.w, r.y}};
    Edge right = {{r.x+r.w, r.y}, {r.x+r.w, r.y+r.h}};
    Edge bottom = {{r.x, r.y+r.h}, {r.x+r.w, r.y+r.h}};
    
    r.left = left;
    r.top = top;
    r.right = right;
    r.bottom = bottom;

    return r;
}

void NGPL_UpdateRect(NGPL_Rect* r)
{
    Edge left = {{r->x, r->y}, {r->x, r->y+r->h}};
    r->left = left;
    Edge top = {{r->x, r->y}, {r->x+r->w, r->y}};
    r->top = top;
    Edge right = {{r->x+r->w, r->y}, {r->x+r->w, r->y+r->h}};
    r->right = right;
    Edge bottom = {{r->x, r->y+r->h}, {r->x+r->w, r->y+r->h}};
    r->bottom = bottom;
}

void NGPL_BlitRect2(Renderer ren, NGPL_Rect* r)
{
    NGPL_DrawEdge(ren, &r->left);
    NGPL_DrawEdge(ren, &r->top);
    NGPL_DrawEdge(ren, &r->right);
    NGPL_DrawEdge(ren, &r->bottom);
}

RigidBody CreateRigidBody(float x, float y, int w , int h)
{
    RigidBody rb;
    rb.mass = 100.0;
    rb.isDynamic = false;
    rb.isStatic = true;
    rb.position.x = x;
    rb.position.y = y;
    rb.velocity.x = 0.0;
    rb.velocity.y = 0.0;
    rb.r = NGPL_CreateRect(w,h,x,y);

    return rb;
}

void NGPL_UpdateRigidBody(RigidBody* rb, float deltaTime)
{
    rb->position.x += rb->velocity.x * deltaTime;
    rb->position.y += rb->velocity.y * deltaTime;
    rb->r.x = rb->position.x;
    rb->r.y = rb->position.y;
    NGPL_UpdateRect(&rb->r);
}

void NGPL_BlitRigidBody(Renderer ren, RigidBody* rb)
{
    NGPL_BlitRect2(ren, &rb->r);
}

void NGPL_SetRigidBodyMass(RigidBody* rb, float nMass)
{
    rb->mass = nMass;
}

void NGPL_SetRigidBodyDynamic(RigidBody* rb, bool isDynamic)
{
    if (isDynamic)
    {
        rb->isDynamic = isDynamic;
        rb->isStatic = false;
    } else {
        rb->isDynamic = false;
        rb->isStatic = isDynamic;
    }
}

void NGPL_InitPSpace(PSpace* space, int cellSize, int nRows, int nCols)
{
    space->cellSize = cellSize;
    space->rows = nRows;
    space->cols = nCols;
    //space->g = 0.0;
    space->g = 9.8;
    space->f = 0.98;

    space->cells = malloc(sizeof(PGridCell*) * space->rows);
    for (int i = 0; i < space->rows; i++)
    {
        space->cells[i] = malloc(sizeof(PGridCell) * space->cols);
        // Init each cell with empty array
        for (int j = 0; j < space->cols; j++)
        {
            space->cells[i][j].entities = NULL;
            space->cells[i][j].entityCount = 0;
        }
    }
}

PSpace NGPL_CreatePhysicsSpace(int cellSize, int nRows, int nCols, int gridX, int gridY)
{
    PSpace space;

    space.bounds.x = gridX;
    space.bounds.y = gridY;
    space.bounds.w = cellSize * nCols;
    space.bounds.h = cellSize * nRows;
    NGPL_InitPSpace(&space, cellSize, nRows, nCols);

    return space;
}

void NGPL_PGCalcFriction(PSpace* space, RigidBody* rb)
{
    if (rb->velocity.x > 0)
    {
        rb->velocity.x -= space->f;
        if (rb->velocity.x < 0)
        {
            rb->velocity.x = 0;
        }
    } else if (rb->velocity.x < 0) {
        rb->velocity.x += space->f;
        if (rb->velocity.x > 0)
        {
            rb->velocity.x = 0;
        }
    }
}

void ApplyForces(PSpace* space, RigidBody* rb)
{
    float gf = (space->g*rb->mass/20.0)*((rb->mass*10)/(rb->mass*10));
    rb->isDynamic ? rb->velocity.y += gf : 0;
    rb->isDynamic ? NGPL_PGCalcFriction(space, rb) : NULL;
}

void NGPL_SetPhysicsSpaceGravity(PSpace* space, float g)
{
    space->g = g;
}

void NGPL_SetPhysicsSpaceFriction(PSpace* space, float f)
{
    space->f = f;
}

void NGPL_GetOccupiedCells(PSpace *space, RigidBody *rb, int *startRow, int *endRow, int *startCol, int *endCol)
{
    *startRow = (int)rb->position.y / space->cellSize;
    *endRow = (int)(rb->position.y + rb->r.h) / space->cellSize;
    *startCol = (int)rb->position.x / space->cellSize;
    *endCol = (int)(rb->position.x + rb->r.w) / space->cellSize;
}

void NGPL_PSpaceAddEntity(PSpace *space, RigidBody *rb)
{
    int startRow, endRow, startCol, endCol;
    NGPL_GetOccupiedCells(space, rb, &startRow, &endRow, &startCol, &endCol);

    for (int row = startRow; row <= endRow; row++) {
        for (int col = startCol; col <= endCol; col++) {
            if (row < 0 || row >= space->rows || col < 0 || col >= space->cols) continue; // Skip out of bounds

            PGridCell *cell = &space->cells[row][col];
            // Resize the entities array to accommodate the new entity
            cell->entities = realloc(cell->entities, (cell->entityCount + 1) * sizeof(RigidBody*));
            if (cell->entities == NULL) {
                // Handle allocation failure
                return;
            }
            // Add the entity to the cell
            cell->entities[cell->entityCount] = rb;
            cell->entityCount++;
        }
    }
}

void NGPL_PSpaceRemEntity(PSpace* space, RigidBody* rb)
{
    int startRow, endRow, startCol, endCol;
    NGPL_GetOccupiedCells(space, rb, &startRow, &endRow, &startCol, &endCol);

    for (int row = startRow; row <= endRow; row++) {
        for (int col = startCol; col <= endCol; col++) {
            if (row < 0 || row >= space->rows || col < 0 || col >= space->cols) continue; // Skip out of bounds

            PGridCell *cell = &space->cells[row][col];
            for (int i = 0; i < cell->entityCount; i++) {
                if (cell->entities[i] == rb) {
                    // Shift remaining entities in the array
                    for (int j = i; j < cell->entityCount - 1; j++) {
                        cell->entities[j] = cell->entities[j + 1];
                    }
                    cell->entityCount--;
                    break;
                }
            }
        }
    }
}

void NGPL_PSpaceShowGrid(Renderer ren, PSpace* space, NGPL_Color gridColor)
{
    // Draw vertical lines
    for (int col = 0; col <= space->cols; ++col) {
        NGPL_Rect verticalLine = NGPL_CreateRect(
            1,
            space->bounds.h,
            space->bounds.x + col * space->cellSize,
            space->bounds.y
        );
        NGPL_BlitRect2(ren, &verticalLine);
    }

    // Draw horizontal lines
    for (int row = 0; row <= space->rows; ++row) {
        NGPL_Rect horizontalLine = NGPL_CreateRect(
            space->bounds.w,
            1,
            space->bounds.x,
            space->bounds.y + row * space->cellSize
        );
        NGPL_BlitRect2(ren, &horizontalLine);
    }
}

void NGPL_PSpaceFree(PSpace* space)
{
    if (space == NULL) return;

    // Iterate over each row
    for (int i = 0; i < space->rows; i++)
    {
        if (space->cells[i] != NULL)
        {
            // Iterate over each column in the row
            for (int j = 0; j < space->cols; j++)
            {
                PGridCell *cell = &space->cells[i][j];
                // Free each entity in the cell
                for (int k = 0; k < cell->entityCount; k++)
                {
                    free(cell->entities[k]);
                }
                // Free the array of entities
                free(cell->entities);
            }
            // Free the column array
            free(space->cells[i]);
        }
    }
    // Free the row array
    free(space->cells);
}

bool NGPL_NegXAABB(RigidBody* rb1, RigidBody* rb2)
{

    if ((int)rb1->r.left.V1.x == (int)rb2->r.right.V1.x & (rb1->r.left.V1.y <= rb2->r.right.V2.y & rb1->r.left.V2.y >= rb2->r.right.V1.y))
    {
        rb1->position.x = rb2->r.x + rb2->r.w+0.1; // Position rb1 to the right of rb2
        rb1->velocity.x = 0.0;
        return true;
    }
    return false;
}

bool NGPL_PosXAABB(RigidBody* rb1, RigidBody* rb2)
{
    if ((int)rb1->r.right.V1.x == (int)rb2->r.left.V1.x & (rb1->r.right.V1.y <= rb2->r.left.V2.y & rb1->r.right.V2.y >= rb2->r.left.V1.y))
    {
        rb1->position.x = rb2->r.x - rb1->r.w-0.1; // Position rb1 to the left of rb2
        rb1->velocity.x = 0.0;
        return true;
    }
    return false;
}

bool NGPL_NegYAABB(RigidBody* rb1, RigidBody* rb2)
{
    if ((int)rb1->r.top.V1.y == (int)rb2->r.bottom.V1.y & (rb1->r.top.V1.x < rb2->r.bottom.V2.x & rb1->r.top.V2.x > rb2->r.bottom.V1.x))
    {
        rb1->position.y = rb2->r.y + rb2->r.h+0.1;
        rb1->velocity.y = 0.0;
        return true;
    }
    return false;
}

bool NGPL_PosYAABB(RigidBody* rb1, RigidBody* rb2)
{
    if ((int)rb1->r.bottom.V1.y == (int)rb2->r.top.V1.y & (rb1->r.bottom.V1.x < rb2->r.top.V2.x & rb1->r.bottom.V2.x > rb2->r.top.V1.x))
    {
        rb1->position.y = rb2->r.y - rb1->r.h-0.1; // Position rb1 to the right of rb2
        rb1->velocity.y = 0.0;
        return true;
    }
    return false;
}

CollisionInfo NGPL_CollisionInfoCheck(RigidBody* dynamicEntity, RigidBody* staticEntity)
{
    CollisionInfo info;
    info.none = true; // No collision detected yet

    // Perform AABB collision check
    bool isCollisionX;
    bool isCollisionY;

    if (dynamicEntity->velocity.x < 0.0)
    {
        info.typeX = L;
        isCollisionX = NGPL_NegXAABB(dynamicEntity, staticEntity);
    } else if (dynamicEntity->velocity.x > 0.0) {
        info.typeX = R;
        isCollisionX = NGPL_PosXAABB(dynamicEntity, staticEntity);
    } else {
        info.typeX = None;
        isCollisionX = false;
    }
    
    if (dynamicEntity->velocity.y < 0.0)
    {
        info.typeY = U;
        isCollisionY = NGPL_NegYAABB(dynamicEntity, staticEntity);
    } else if (dynamicEntity->velocity.y > 0.0) {
        info.typeY = D;
        isCollisionY = NGPL_PosYAABB(dynamicEntity, staticEntity);
    } else {
        info.typeY = None;
        isCollisionY = false;
    }

    if (isCollisionX || isCollisionY)
    {
        // Collision detected, calculate collision point
        info.none = false;
        info.point.x = (max(dynamicEntity->r.left.V1.x, staticEntity->r.left.V1.x) + min(dynamicEntity->r.right.V1.x, staticEntity->r.right.V1.x)) / 2;
        info.point.y = (max(dynamicEntity->r.top.V1.y, staticEntity->r.top.V1.y) + min(dynamicEntity->r.bottom.V1.y, staticEntity->r.bottom.V1.y)) / 2;
    }

    // Populate other collision details
    info.dE = dynamicEntity;
    info.sE = dynamicEntity;
    info.massDynamic = dynamicEntity->mass;
    info.massStatic = staticEntity->mass;
    info.velocityDynamic = dynamicEntity->velocity;

    return info;
}

RigidBody* GetDynamicEntityFromCollisionInfo(CollisionInfo collision)
{
    // Get the entity from the PGridSpace 
    return collision.dE;
}

RigidBody* GetStaticEntityFromCollisionInfo(CollisionInfo collision)
{
    // Get the entity from the PGridSpace 
    return collision.dE;
}

void NGPL_ResolveCollision(PSpace* space, CollisionInfo collision, float deltaTime)
{
    RigidBody* dynamicEntity = GetDynamicEntityFromCollisionInfo(collision);
    RigidBody* staticEntity = GetStaticEntityFromCollisionInfo(collision);
    
    // Collision resolution ( bouncing off, rotating, etc.)
    if (collision.typeX == R & collision.typeY == D) // Right and Down
    {
        return;
        // printf("right and down coll\n");
    }
    if (collision.typeX == L & collision.typeY == D) // Left and Down
    {
        return;
        // printf("Left and down coll\n");
    }
    if (collision.typeX == L & collision.typeY == U) // Left and Up
    {
        return;
        // printf("Left and up coll\n");
    }
    if (collision.typeX == R & collision.typeY == U) // Right and Up
    {
        return;
        // printf("Right and up coll\n");
    }
    if (collision.typeX == L & collision.typeY == None) // Left
    {
        return;
        // printf("Left coll\n");
    }
    if (collision.typeX == R & collision.typeY == None) // Right
    {
        return;
        // printf("Right coll\n");
    }
    if (collision.typeX == None & collision.typeY == U) // Up
    {
        return;
        // printf("Up coll\n");
    }
    if (collision.typeX == None & collision.typeY == D) // Down
    {
        return;
        // printf("Down coll\n");
    }
    
    //printf("RESOLVING | Collision detected @: %0.1f | %0.1f\n", collision.point.x, collision.point.y);
}

bool NGPL_PSpaceObserve(PSpace* space, float deltaTime)
{
    bool collisionDetected = false;
    for (int row = 0; row < space->rows; row++)
    {
        for (int col = 0; col < space->cols; col++)
        {
            PGridCell *cell = &space->cells[row][col];
            for (int i = 0; i < cell->entityCount; i++)
            {
                RigidBody *entityA = cell->entities[i];
                // Check only if entityA is dynamic
                if (entityA->isDynamic)
                {
                    // Now check against all other entities
                    for (int j = 0; j < cell->entityCount; j++)
                    {
                        if (i == j) continue; // Skip checking against itself

                        RigidBody *entityB = cell->entities[j];

                        // Check only if entityB is static
                        if (entityB->isStatic)
                        {
                            CollisionInfo collision = NGPL_CollisionInfoCheck(entityA, entityB);
                            if (!collision.none) 
                            {
                                NGPL_ResolveCollision(space, collision, deltaTime);
                                collisionDetected = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return collisionDetected;
}

void NGPL_PSpaceEntityUpdate(PSpace* space, RigidBody* rb, float deltaTime, int CCD_Step, Renderer ren)
{
    int STEPS_FOR_CCD = CCD_Step > 0 ? CCD_Step : 100;
    float stepDelta = deltaTime / STEPS_FOR_CCD;

    for (int step = 0; step < STEPS_FOR_CCD; ++step) {
        // Update Entity position
        NGPL_UpdateRigidBody(rb, stepDelta);

        // Constrain position within the bounds of the physics space
        rb->position.x = max(space->bounds.x, min(rb->position.x, space->bounds.x + space->bounds.w - rb->r.w));
        rb->position.y = max(space->bounds.y, min(rb->position.y, space->bounds.y + space->bounds.h - rb->r.h));
        NGPL_UpdateRect(&rb->r);  // Update the collider/rectangle after adjusting the position

        // Calculate and update the current row and column
        int newRow = (rb->position.y - space->bounds.y) / space->cellSize;
        int newCol = (rb->position.x - space->bounds.x) / space->cellSize;

        // Check if the entity has moved to a new cell
        if (newRow != rb->cRow || newCol != rb->cCol) {
            if (newRow >= 0 && newRow < space->rows && newCol >= 0 && newCol < space->cols) {
                // Remove entity from the old cell
                NGPL_PSpaceRemEntity(space, rb);

                // Update current row and column
                rb->cRow = newRow;
                rb->cCol = newCol;

                // Add entity to the new cell
                NGPL_PSpaceAddEntity(space, rb);
            }
        }
        // Check for collisions at this step
        bool collisionDetected = NGPL_PSpaceObserve(space, deltaTime);
    }

    // Final update for current row and column after all movements
    rb->cRow = (rb->position.y - space->bounds.y) / space->cellSize;
    rb->cCol = (rb->position.x - space->bounds.x) / space->cellSize;

}
