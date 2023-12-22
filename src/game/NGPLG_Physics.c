#include "../../include/NGPLG_Physics.h"



void NGPL_UpdateEntityX(NGPL_Entity* e, float deltaTime, float friction)
{
    if (e->velocity.x > 0) {
        e->velocity.x -= friction;
        if (e->velocity.x < 0) {
            e->velocity.x = 0;
        }
    } else if (e->velocity.x < 0) {
        e->velocity.x += friction;
        if (e->velocity.x > 0) {
            e->velocity.x = 0;
        }
    }
    e->position.x += e->velocity.x * deltaTime;
    e->sprite->rect.x = e->position.x;
}

void NGPL_UpdateEntityY(NGPL_Entity* e, float deltaTime)
{
    e->position.y += e->velocity.y * deltaTime;
    e->sprite->rect.y = e->position.y;
}

void NGPL_ApplyGravity(NGPL_Entity* e, float g)
{
    float f = (g*e->mass/20.0)*((e->mass*10)/(e->mass*10));
    e->dynamic ? e->velocity.y += f : 0;
    //printf("G=%0.2fpps\n",f);
}

void NGPL_Physics(NGPL_EntityPool* pool, float friction, float gravity, float deltaTime)
{
    for (int i = 0; i < pool->count; i++)
    {
        NGPL_UpdateEntityX(pool->pool[i], deltaTime, friction);
        NGPL_ApplyGravity(pool->pool[i], gravity);
        NGPL_UpdateEntityY(pool->pool[i], deltaTime);
    }
}


