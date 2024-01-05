#include "../../include/NDL.h"



Uint32 Video_SubSystem = SDL_INIT_VIDEO;
Uint32 Audio_SubSystem = SDL_INIT_AUDIO;
Uint32 Timer_SubSystem = SDL_INIT_TIMER;
Uint32 Events_SubSystem = SDL_INIT_EVENTS;
Uint32 All_SubSystem = SDL_INIT_EVERYTHING;
Uint32 Joystick_SubSystem = SDL_INIT_JOYSTICK;
Uint32 Controller_SubSystem = SDL_INIT_GAMECONTROLLER;




NDL_Entity* CreateEntity()
{
    NDL_Entity* e = malloc(sizeof(NDL_Entity));
    e->tag = NULL;
    e->sprite = NULL;
    e->collider = NULL;
    e->isDynamic = false;
    e->componentFlags = NO_COMPONENT;
    return e;
}

Pool* CreatePool(int poolSize)
{
    Pool* pool = malloc(sizeof(Pool));
    pool->size = 0;
    pool->maxSize = poolSize;
    pool->entities = malloc(sizeof(NDL_Entity)*pool->size);
    for (int i = 0; i < pool->size; ++i)
    {
        pool->entities[i] = NULL;
    }
    return pool;
}

void AddToPool(NDL_Entity* e, Pool* pool)
{
    if (pool->size >= pool->maxSize)
    {
        printf("This Pool is full!\n");
        return;
    }
    pool->entities[pool->size] = e;
    ++pool->size;
}

ColliderComponent* CreateColliderComponent(float x, float y, int w, int h)
{
    ColliderComponent* collider = malloc(sizeof(ColliderComponent)); // Dynamically allocate memory for NDL_RigidBody
    if (collider == NULL) {
        // Handle the error in case malloc fails
        return NULL;
    }

    collider->mass = 100.0;
    collider->isStatic = true;
    collider->isDynamic = false;
    // Constrain position within the bounds of the physics space
    collider->position.x = x;
    collider->position.y = y;
    collider->velocity.x = 0.0;
    collider->velocity.y = 0.0;
    collider->r = NDL_CreateRect(w, h, x, y);

    return collider; // Return a pointer to the newly created NDL_RigidBody
}

void AddSpriteComponent(NDL_Entity *entity, Vector2 size, NDL_Color spriteColor)
{
    SpriteComponent* sprite = malloc(sizeof(SpriteComponent));
    sprite->color = spriteColor;
    sprite->imageOffset = (Vector2){0,0};
    sprite->imageRect = (Rect){0,0,size.x,size.y};
    sprite->image = NULL;
    entity->sprite = sprite;
    entity->componentFlags |= SPRITE_COMPONENT;
}

void AddColliderComponent(NDL_Entity* entity, Vector2 size, NDL_Color colliderColor)
{
    ColliderComponent* collider = CreateColliderComponent(entity->position.x, entity->position.y, size.x, size.y);
    entity->collider = collider;
    entity->componentFlags |= COLLIDER_COMPONENT;
    if (entity->collider == NULL)
    {
        printf("Error adding collider component!\n");
        return;
    }
}

void RemComponent(NDL_Entity* e, Components component)
{
    e->componentFlags &= ~component;
}

bool HasComponent(NDL_Entity* e, Components component)
{
    return (e->componentFlags & component) == component;
}

void AddSpriteTexture(Renderer ren, NDL_Entity* e, const char* fp)
{
    e->sprite->image = NDL_CreateTexture(ren, fp);
    if (e->sprite->image == NULL)
    {
        printf("Error creating texture!\n");
        return;
    }
}

void SetEntityTag(NDL_Entity* entity, const char* tag)
{
    entity->tag = tag;
}

void SetEntityDynamic(NDL_Entity* entity, bool set)
{
    entity->isDynamic = set;
}

void SetEntityMass(NDL_Entity* e, float mass)
{
    e->collider->mass = mass;
}

void RemEntityTag(NDL_Entity* entity)
{
    entity->tag = NULL;
}

void RemSpriteComponent(NDL_Entity* entity)
{
    RemComponent(entity, SPRITE_COMPONENT);
    entity->sprite = NULL;
}

void RemColliderComponent(NDL_Entity* entity)
{
    RemComponent(entity, COLLIDER_COMPONENT);
    entity->collider = NULL;
}

void UpdateSystem(RenderSystem* renSys, PhysicsSystem* physicsSystem, float deltaTime, int UPF)
{
    for (int i = 0; i < physicsSystem->gridSpace->r; ++i)   // rows
    {
        for (int j = 0; j < physicsSystem->gridSpace->c; ++j)   // cols
        {
            Cell cell = physicsSystem->gridSpace->cells[i][j];
            renSys->pool = cell.pool;
            for (int e = 0; e < cell.pool->size; ++e)
            {
                NDL_Entity* entity = cell.pool->entities[e];
                entity->collider->velocity = entity->velocity;
                if (HasComponent(entity, COLLIDER_COMPONENT))
                {
                    if (entity->isDynamic)
                    {
                        physicsSystem->handleForces(entity, physicsSystem);

                    }
                }
                physicsSystem->handlePositions(physicsSystem, entity, deltaTime, UPF);
            }
        }

    }
}

void SetPhysicsSystemGravity(PhysicsSystem* phys, float gravity)
{
    phys->gravity = gravity;
}

void SetPhysicsSystemFrictionX(PhysicsSystem* phys, float frictionX)
{
    phys->friction.x = frictionX;
}

void SetPhysicsSystemFrictionY(PhysicsSystem* phys, float frictionY)
{
    phys->friction.x = frictionY;
}

bool EnablePhysicsSystemFrictionX(PhysicsSystem* phys, bool frictionX)
{
    phys->frictionX = frictionX;
    return phys->frictionX;
}

bool EnablePhysicsSystemFrictionY(PhysicsSystem* phys, bool frictionY)
{
    phys->frictionY = frictionY;
    return phys->frictionY;
}

/*
 * Function: NDL_Test
 * ----------------------------
 * Returns a test message if NDL is initialize correctly.
 *
 * Returns: 
 *   A character array.
 */
char* NDL_Test()
{
    return "\nNDL Test\n";
}

/*
 * Function: NDL_Init
 * ---------------------------
 * Attempts to initialize the core components of NDL (SDL2,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void
 */
void NDL_Init()
{
    if (SDL_Init(Video_SubSystem) != 0)
    {
        fprintf(stderr, "\nFailed to initialize core NDL components...\n%s\n",SDL_GetError());
    } else {
        printf("\nNDL Initialized!\n");
    }
}

/*
 * Function: NDL_InitG
 * ---------------------------
 * Attempts to initialize the core components of NDL Game (SDL2_Image,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void
 */
void NDL_InitG()
{
    if (!IMG_Init(IMG_INIT_PNG|IMG_INIT_PNG|IMG_INIT_WEBP))
    {
        printf("\nFailed to initialize core NDL Game components...\n%s\n",IMG_GetError);
    } else {
        printf("\nNDLG Initialized!\n");
    }
}

/*
 * Function: NDL_InitSubSystem
 * ---------------------------
 * Attempts to initialize the SubSystem passed in.
 * Prints a success message if components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *   Void.
 */
int NDL_InitSubSystem(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0)
    {
        fprintf(stderr, "\nFailed to initialize SubSystem...\n%s\n",SDL_GetError());
        return 1;
    } else {
        printf("\nSubSystem Initialized!\n");
        return 0;
    }
}

/*
 * Function: NDL_GetKey
 * -----------------------------------------
 * Retrieves the key code from an SDL keyboard event.
 *
 * This function extracts the key code from an SDL_Event that is expected to be
 * of a keyboard event type (SDL_KEYDOWN or SDL_KEYUP). It should be used only
 * when handling these specific event types.
 *
 * event: An SDL_Event from which to extract the key code.
 *
 * Returns:
 *   The SDL scancode corresponding to the key in the event.
 *   If the event is not a keyboard event, SDL_SCANCODE_UNKNOWN is returned.
 */
int NDL_GetKey(Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        return event.key.keysym.scancode;
    }
    return SDL_SCANCODE_UNKNOWN;
}

/*
 * Function: NDL_GetEvent
 * -----------------------------------------
 * Polls for and processes the next event in the SDL event queue.
 *
 * This function should be called in the game's main loop to handle input
 * and system events. It can handle keyboard, mouse, window, and other SDL
 * events, and should be extended or modified as necessary for specific game
 * requirements.
 *
 * event: A pointer to an Event structure where the event data will be stored.
 *
 * Returns:
 *   True if an event was processed, false if the event queue is empty.
 */
bool NDL_GetEvent(Event* event, Window window, Renderer renderer) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                // Handle Quit event (e.g., window close)
                SDL_DestroyWindow(window);
	            SDL_DestroyRenderer(renderer);
	            SDL_Quit();
                break;
            default:
                break;
        }
        return true;
    }
    return false;
}

/*
 * Function: NDL_CleanUp
 * -----------------------
 * Cleans up SDL resources and shuts down SDL subsystems.
 *
 * This function releases SDL resources, such as the renderer and window, and
 * then calls SDL_Quit to shut down all SDL subsystems. It should be called at the end of
 * the game to ensure proper resource management and clean exit.
 *
 * Parameters:
 *   renderer: The SDL_Renderer object to be destroyed.
 *   window: The SDL_Window object to be destroyed.
 *
 * Returns:
 *   void: This function does not return a value.
 */
void NDL_CleanUp(Renderer renderer, Window window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
 * Function: NDL_GetKeyState
 * --------------------------
 * Retrieves the current state of the keyboard.
 *
 * This function calls SDL_GetKeyboardState to obtain the current key states of the keyboard.
 * It can be used to check which keys are currently pressed or released. The function is typically
 * called each frame to update the game's response to player input.
 *
 * Parameters:
 *   numKeys: An optional pointer to an int that receives the number of keys in the returned array.
 *            Pass NULL if you do not need this information.
 *
 * Returns:
 *   const Uint8*: A pointer to an array of key states. Each element in the array corresponds to a key,
 *   and its value will be 1 if the key is pressed and 0 if it is not.
 */
const Uint8* NDL_GetKeyState(int* numKeys)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(numKeys);
    return keyboardState;
}
