#include "../../include/NGPLG.h"
#include "../../include/NGPLG_Physics.h"


/*
 * Function: NGPL_InitG
 * ---------------------------
 * Attempts to initialize the core components of NGPL Game (SDL2_Image,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void
 */
void NGPL_InitG()
{
    if (!IMG_Init(IMG_INIT_PNG|IMG_INIT_PNG|IMG_INIT_WEBP))
    {
        printf("\nFailed to initialize core NGPL Game components...\n%s\n",IMG_GetError);
    } else {
        printf("\nNGPLG Initialized!\n");
    }
}

/*
 * Function: NGPL_OpenController
 * -----------------------------------------
 * Initializes the SDL game controller subsystem and opens the first available controller.
 *
 * This function will attempt to find and open the first connected game controller.
 * It initializes the SDL game controller subsystem if not already initialized.
 *
 * Returns:
 *   A pointer to an SDL_GameController Entity if a controller is successfully opened,
 *   NULL otherwise.
 */
Controller NGPL_OpenController() 
{
    if (NGPL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) 
    {
        SDL_Log("Unable to initialize SDL Game Controller Subsystem: %s", SDL_GetError());
        return NULL;
    }

    // Attempt to open the first available controller
    for (int i = 0; i < SDL_NumJoysticks(); ++i) 
    {
        if (SDL_IsGameController(i)) 
        {
            Controller controller = SDL_GameControllerOpen(i);
            if (controller) 
            {
                SDL_Log("Controller opened: %s", SDL_GameControllerName(controller));
                return controller; // Controller found and opened
            }
        }
    }

    SDL_Log("No available controllers found");
    return NULL;
}

/*
 * Function: NGPL_GetPlayerActions
 * -----------------------------------------
 * Retrieves the current player actions based on the key state.
 *
 * This function checks the current state of key bindings and returns
 * a bitwise OR of PlayerActions enum values corresponding to the actions
 * that are currently active based on the key states.
 *
 * Returns:
 *   PlayerActions: An integer representing the bitwise OR of the actions
 *   currently being performed by the player. The value is a combination of
 *   PLAYER_ACTION_MOVE_LEFT, PLAYER_ACTION_MOVE_RIGHT, PLAYER_ACTION_JUMP,
 *   and PLAYER_ACTION_MENU, depending on the key states.
 */
PlayerActions NGPL_GetPlayerActions() 
{
    const Uint8* state = NGPL_GetKeyState(NULL);
    PlayerActions actions = PLAYER_ACTION_NONE;

    if (state[keyBinds.moveLeft]) 
    {
        actions |= PLAYER_ACTION_MOVE_LEFT;
    }
    if (state[keyBinds.moveRight]) 
    {
        actions |= PLAYER_ACTION_MOVE_RIGHT;
    }
    if (state[keyBinds.jump]) 
    {
        actions |= PLAYER_ACTION_JUMP;
    }
    if (state[keyBinds.menu]) 
    {
        actions |= PLAYER_ACTION_MENU;
    }

    return actions;
}

/*
 * Function: NGPL_SetKeyBinds
 * -----------------------------------------
 * Sets the key bindings for player actions.
 *
 * This function assigns SDL scancodes to various player actions including moving left,
 * moving right, jumping, and accessing the menu. These scancodes are used to determine
 * the player's actions in the game.
 *
 * Parameters:
 *   moveLeft: SDL_Scancode for the action to move the player left.
 *   moveRight: SDL_Scancode for the action to move the player right.
 *   jump: SDL_Scancode for the action to make the player jump.
 *   menu: SDL_Scancode for the action to open the game menu.
 *
 * Returns:
 *   void: This function does not return a value.
 */
void NGPL_SetKeyBinds(SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode menu) 
{
    keyBinds.moveLeft = moveLeft;
    keyBinds.moveRight = moveRight;
    keyBinds.jump = jump;
    keyBinds.menu = menu;
}

/*
 * Function: NGPL_CreateEntity
 * ---------------------------
 * Creates and initializes an Entity structure.
 *
 * This function sets up an Entity with specified position, size, and default
 * values for velocity and color. It's used for creating new game objects.
 *
 * Parameters:
 *   position: An array of 2 floats representing the initial position of the Entity.
 *   size: An array of 2 floats representing the size of the Entity.
 *
 * Returns:
 *   Entity: The newly created and initialized game Entity.
 */
NGPL_Entity NGPL_CreateEntity(int color[4], float size[2], float position[2], int renderLayer, Renderer renderer) {
    NGPL_Entity entity;
    entity.tag = NULL;
    entity.size.x = size[0];
    entity.size.y = size[1];
    entity.dynamic = false;
    entity.mass = 100.0;
    entity.position.x = position[0];
    entity.position.y = position[1];
    entity.velocity.x = 0.0;
    entity.velocity.y = 0.0;
    entity.sprite = NGPL_CreateSprite(position, size, renderLayer, renderer);
    entity.sprite->color.r = color[0];
    entity.sprite->color.g = color[1];
    entity.sprite->color.b = color[2];
    entity.sprite->color.a = color[3];

    return entity;
}

/*
 * Function: NGPL_CreateTexture
 * ----------------------------
 * Creates an SDL texture for rendering.
 *
 * This function creates an SDL texture using the specified width and height.
 * The texture is intended for rendering in the provided renderer context.
 *
 * Parameters:
 *   renderer: Pointer to the SDL renderer where the texture will be used.
 *   w: Width of the texture.
 *   h: Height of the texture.
 *
 * Returns:
 *   NGPL_Texture*: Pointer to the created SDL texture.
 */
NGPL_Texture* NGPL_CreateTexture(Renderer renderer, const char* fp)
{
    if (!fp)
    {
        NGPL_Texture* texture = IMG_LoadTexture(renderer, "..\\..\\common\\txtrDefault.png");
        return texture;
    } else {
        NGPL_Texture* texture = IMG_LoadTexture(renderer, fp);
        return texture;
    }
}

/*
 * Function: NGPL_DestroyTexture
 * -----------------------------
 * Frees the memory associated with an SDL texture.
 *
 * This function destroys an SDL texture, freeing the memory it occupies.
 *
 * Parameters:
 *   texture: Pointer to the NGPL_Texture to be destroyed.
 */
void NGPL_DestroyTexture(NGPL_Texture* texture)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

/*
 * Function: NGPL_CreateTextureCache
 * ---------------------------------
 * Creates a texture cache to store and manage textures.
 *
 * This function initializes a texture cache with a specified maximum size.
 * It allocates memory for the texture cache and its entries.
 *
 * Parameters:
 *   maxSize: The maximum number of textures the cache can hold.
 *
 * Returns:
 *   NGPL_TextureCache*: Pointer to the newly created texture cache.
 */
NGPL_TextureCache* NGPL_CreateTextureCache(int maxSize) 
{
    NGPL_TextureCache* cache = (NGPL_TextureCache*)malloc(sizeof(NGPL_TextureCache));
    if (cache) 
    {
        cache->entries = (NGPL_TextureCacheEntry*)malloc(sizeof(NGPL_TextureCacheEntry) * maxSize);
        if (cache->entries) 
        {
            cache->size = 0;
            cache->maxSize = maxSize;
        } else {
            free(cache);
            return NULL;
        }
    }
    return cache;
}

/*
 * Function: NGPL_DestroyTextureCache
 * ----------------------------------
 * Destroys a texture cache and frees its resources.
 *
 * This function frees all textures stored in the cache and then frees
 * the memory allocated for the cache itself.
 *
 * Parameters:
 *   cache: Pointer to the NGPL_TextureCache to be destroyed.
 */
void NGPL_DestroyTextureCache(NGPL_TextureCache* cache) 
{
    if (cache) 
    {
        for (int i = 0; i < cache->size; i++) 
        {
            SDL_DestroyTexture(cache->entries[i].texture);
        }
        free(cache->entries); // Free the entries array
        free(cache);
    }
}

/*
 * Function: NGPL_TextureCacheGet
 * ------------------------------
 * Retrieves a texture from the texture cache.
 *
 * This function searches for a texture in the cache using a specified key.
 * If found, it increments the texture's usage frequency.
 *
 * Parameters:
 *   cache: Pointer to the texture cache.
 *   key: Key used to search for the texture in the cache.
 *
 * Returns:
 *   NGPL_Texture*: Pointer to the found texture, or NULL if not found.
 */
NGPL_Texture* NGPL_TextureCacheGet(NGPL_TextureCache* cache, const char* key) 
{
    for (int i = 0; i < cache->size; i++) 
    {
        if (strcmp(cache->entries[i].key, key) == 0) 
        {
            cache->entries[i].frequency++;
            return cache->entries[i].texture;
        }
    }
    return NULL; // Key not found
}

/*
 * Function: NGPL_TextureCachePut
 * ------------------------------
 * Adds a texture to the texture cache.
 *
 * This function adds a new texture to the cache. If the cache is full,
 * it evicts the least frequently used texture to make room.
 *
 * Parameters:
 *   cache: Pointer to the texture cache.
 *   key: Key to associate with the texture in the cache.
 *   texture: Pointer to the NGPL_Texture to be added to the cache.
 *
 * Returns:
 *   int: 0 on success, non-zero on failure.
 */
int NGPL_TextureCachePut(NGPL_TextureCache* cache, const char* key, NGPL_Texture* texture) 
{
    if (cache->size >= cache->maxSize) 
    {
        // Evict the least frequently used texture
        int minFreqIndex = 0;
        for (int i = 1; i < cache->size; i++) 
        {
            if (cache->entries[i].frequency < cache->entries[minFreqIndex].frequency) 
            {
                minFreqIndex = i;
            }
        }

        NGPL_DestroyTexture(cache->entries[minFreqIndex].texture); // Free the least used texture
        memmove(&cache->entries[minFreqIndex], &cache->entries[minFreqIndex + 1], sizeof(NGPL_TextureCacheEntry) * (cache->size - minFreqIndex - 1));
        cache->size--;
    }

    // Add the new texture
    strncpy(cache->entries[cache->size].key, key, MAX_CACHE_KEY_SIZE - 1);
    cache->entries[cache->size].key[MAX_CACHE_KEY_SIZE - 1] = '\0'; // Ensure null-termination
    cache->entries[cache->size].texture = texture;
    cache->entries[cache->size].frequency = 1;
    cache->size++;
    return 0;
}

/*
 * Function: NGPL_CreateAssetManager
 * ---------------------------------
 * Creates an asset manager with a texture cache.
 *
 * This function initializes an asset manager and sets up a texture cache
 * with the specified size.
 *
 * Parameters:
 *   cacheSize: The size of the texture cache within the asset manager.
 *
 * Returns:
 *   NGPL_AssetManager*: Pointer to the newly created asset manager.
 */
NGPL_AssetManager* NGPL_CreateAssetManager(int cacheSize) 
{
    NGPL_AssetManager* manager = (NGPL_AssetManager*)malloc(sizeof(NGPL_AssetManager));
    if (manager) 
    {
        manager->textureCache = NGPL_CreateTextureCache(cacheSize);
        if (!manager->textureCache) 
        {
            free(manager);
            return NULL;
        }
    }
    return manager;
}

/*
 * Function: NGPL_LoadTextureAsset
 * -------------------------------
 * Loads a texture from a file and adds it to the asset manager's cache.
 *
 * This function loads an image from a specified file path, creates a texture
 * from it, and stores the texture in the asset manager's texture cache.
 *
 * Parameters:
 *   manager: Pointer to the asset manager.
 *   renderer: Pointer to the SDL renderer.
 *   assetKey: Key to associate with the loaded texture in the cache.
 *   filePath: File path of the image to load.
 *
 * Returns:
 *   int: 0 on success, non-zero on failure.
 */
int NGPL_LoadTextureAsset(NGPL_AssetManager* manager, Renderer renderer, const char* assetKey, const char* filePath) 
{
    NGPL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (!texture) 
    {
        printf("Unable to load image: %s\n", IMG_GetError());
        printf("Unable to create texture: %s\n", SDL_GetError());
        return -1;
    }
    return NGPL_TextureCachePut(manager->textureCache, assetKey, texture);
}

/*
 * Function: NGPL_GetTextureAsset
 * ------------------------------
 * Retrieves a texture from the asset manager's cache.
 *
 * This function searches for a texture in the asset manager's cache using
 * a specified key.
 *
 * Parameters:
 *   manager: Pointer to the asset manager.
 *   assetKey: Key used to search for the texture in the cache.
 *
 * Returns:
 *   NGPL_Texture*: Pointer to the found texture, or NULL if not found.
 */
NGPL_Texture* NGPL_GetTextureAsset(NGPL_AssetManager* manager, const char* assetKey) 
{
    return (NGPL_Texture*)NGPL_TextureCacheGet(manager->textureCache, assetKey);
}

/*
 * Function: NGPL_DestroyAssetManager
 * ----------------------------------
 * Destroys an asset manager and frees its resources.
 *
 * This function frees all resources associated with the asset manager,
 * including its texture cache.
 *
 * Parameters:
 *   manager: Pointer to the NGPL_AssetManager to be destroyed.
 */
void NGPL_DestroyAssetManager(NGPL_AssetManager *manager) 
{
    if (manager) 
    {
        NGPL_DestroyTextureCache(manager->textureCache);
        free(manager);
    }
}

/*
 * Function: NGPL_CreateSprite
 * ---------------------------
 * Creates a new sprite with a given texture, position, size, and rendering layer.
 *
 * Parameters:
 *   texture: Pointer to the NGPL_Texture to be used for the sprite.
 *   position: Array of 2 floats representing the sprite's position.
 *   size: Array of 2 floats representing the sprite's size.
 *   rendererLayer: Integer representing the layer on which the sprite should be rendered.
 *   renderer: Pointer to the SDL renderer.
 *
 * Returns:
 *   NGPL_Sprite*: Pointer to the newly created sprite.
 */
NGPL_Sprite* NGPL_CreateSprite(float position[2], float size[2], int rendererLayer, Renderer renderer)
{
    NGPL_Sprite* sprite = (NGPL_Sprite*)malloc(sizeof(NGPL_Sprite));
    if (!sprite) {
        // Handle memory allocation failure
        printf("MEM ERROR FOR SPRITE CREATION");
        return NULL;
    }
    sprite->rect.w = size[0];
    sprite->rect.h = size[1];
    sprite->rect.x = position[0];
    sprite->rect.y = position[1];
    sprite->renderLayer = rendererLayer;
    NGPL_SetSpriteRectPoints(sprite);
    return sprite;
}

/*
 * Function: NGPL_CreateRenderSys
 * ------------------------------
 * Initializes and creates a rendering system for NGPL_Sprite(s).
 *
 * Parameters:
 *   sdlRenderer: Pointer to the SDL renderer.
 *
 * Returns:
 *   NGPL_RenderSys*: Pointer to the newly created rendering system.
 */
NGPL_RenderSys* NGPL_CreateRenderSys(Renderer sdlRenderer)
{
    NGPL_RenderSys* renderer = (NGPL_RenderSys*)malloc(sizeof(NGPL_RenderSys));
    if (renderer)
    {
        renderer->entities = (NGPL_Entity**)malloc(sizeof(NGPL_Entity*) * INITIAL_RENDER_SYS_CAPACITY);
        if (!renderer->entities)
        {
            free(renderer); // Handle allocation failure for entities
            return NULL;
        }
        renderer->entityCount = 0;
        renderer->capacity = INITIAL_RENDER_SYS_CAPACITY;
        renderer->sdlRenderer = sdlRenderer;
        SDL_RenderGetViewport(sdlRenderer, &renderer->viewport);
    }
    return renderer;
}

/*
 * Function: NGPL_DestroyRenderSys
 * -------------------------------
 * Cleans up and frees resources allocated for a rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_RenderSys to be destroyed.
 */
void NGPL_DestroyRenderSys(NGPL_RenderSys* renderer) 
{
    if (renderer) 
    {
        for (int i = 0; i < renderer->entityCount; i++) 
        {
            NGPL_Entity* entity = renderer->entities[i];
            if (entity) 
            {
                // Assuming NGPL_DestroySprite is a function that frees a sprite
                if (entity->sprite) 
                {
                    NGPL_DestroySprite(entity->sprite);
                }
                free(entity);
            }
        }
        free(renderer->entities);
        free(renderer);
    }
}

/*
 * Function: NGPL_RSAddEntity
 * --------------------------
 * Adds a sprite struct from a NGPL_Sprite pointer passed in, to the rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_RenderSys.
 *   texture: Pointer to the SDL_Texture to be used for the sprite.
 *   rect: SDL_Rect structure defining the sprite's position and size.
 *   layer: Integer specifying the rendering layer of the sprite.
 */
void NGPL_RSAddEntity(NGPL_RenderSys* renderer, NGPL_Entity* entity)
{
    if (entity == NULL || entity->sprite == NULL)
    {
        return; // Handle null entity or sprite
    }

    if (renderer->entityCount >= renderer->capacity)
    {
        // Dynamic resizing of sprite array
        int newCapacity = renderer->capacity * 2;
        NGPL_Entity** newEntities = (NGPL_Entity**)realloc(renderer->entities, sizeof(NGPL_Entity*) * newCapacity);
        if (newEntities)
        {
            renderer->entities = newEntities;
            renderer->capacity = newCapacity;
        } else {
            return; // Handle allocation failure
        }
    }

    renderer->entities[renderer->entityCount++] = entity;
}

/*
 * Function: NGPL_RSRemoveEntity
 * -----------------------------
 * Removes a sprite from the rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_RenderSys.
 *   texture: Pointer to the SDL_Texture of the sprite to be removed.
 */
void NGPL_RSRemoveEntity(NGPL_RenderSys* renderer, NGPL_Texture* texture)
{
    for (int i = 0; i < renderer->entityCount; i++) 
    {
        memmove(&renderer->entities[i], &renderer->entities[i + 1], sizeof(NGPL_Entity*) * (renderer->entityCount - i - 1));
        renderer->entityCount--;
        break;
    }
}

/*
 * Function: NGPL_RSCompareEntities
 * -------------------------------
 * Comparison function used for sorting entities by their rendering layers.
 * 
 * This function is used within NGPL_RSSortSprites(). There really shouldn't be a need for you to call it again.
 *
 * Parameters:
 *   a: Pointer to the first NGPL_Entity.
 *   b: Pointer to the second NGPL_Entity.
 *
 * Returns:
 *   int: Negative if sprite A should render before sprite B, positive otherwise.
 */
int NGPL_RSCompareEntities(const void* a, const void* b)
{
    NGPL_Entity* entityA = *(NGPL_Entity**)a;
    NGPL_Entity* entityB = *(NGPL_Entity**)b;
    if (!entityA->sprite || !entityB->sprite) return 0;
    return (entityA->sprite->renderLayer - entityB->sprite->renderLayer);
}

/*
 * Function: NGPL_RSSortEntities
 * ----------------------------
 * Sorts entities in a rendering system based on their layer.
 * * This function is used within NGPL_RSRender(). There really shouldn't be a need for you to call it again.
 * Parameters:
 *   renderer: Pointer to the NGPL_RenderSys.
 */
void NGPL_RSSortEntities(NGPL_RenderSys* renderer)
{
    qsort(renderer->entities, renderer->entityCount, sizeof(NGPL_Entity*), NGPL_RSCompareEntities);
}

/*
 * Function: NGPL_RSRender
 * -----------------------
 * Renders all entities in the rendering system.
 * If an Entity's sprite->texture is NULL then it will render that sprite's rect.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_RenderSys.
 */
void NGPL_RSRender(NGPL_RenderSys* renderer, int clearColor[4], bool showRect)
{
    NGPL_RSSortEntities(renderer);

    NGPL_ClearScreen(renderer->sdlRenderer, clearColor);

    for (int i = 0; i < renderer->entityCount; i++)
    {
        NGPL_Entity* entity = renderer->entities[i];
        NGPL_Sprite* sprite = entity->sprite;
        Rect renderRect = sprite->rect;

        if (showRect)
        {
            //NGPL_BlitRect(renderer->sdlRenderer, &renderRect);
        }
        SDL_RenderCopy(renderer->sdlRenderer, sprite->image, NULL, &renderRect);
    }
}

/*
 * Function: NGPL_DestroySprite
 * ----------------------------
 * Frees the memory allocated for an NGPL_Sprite object. If the sprite has an associated
 * texture, it also frees the texture.
 *
 * Parameters:
 *   sprite: Pointer to the NGPL_Sprite to be destroyed. If this is NULL, the function
 *           has no effect.
 *
 * Note:
 *   This function assumes ownership of the texture linked to the sprite, meaning
 *   it will also manage the memory for the texture.
 */
void NGPL_DestroySprite(NGPL_Sprite* sprite)
{
    if (sprite) 
    {
        // Assuming the sprite owns the texture and should free it
        NGPL_DestroyTexture(sprite->image);
        free(sprite);
    }
}

/*
 * Function: NGPL_GameCleanUp
 * --------------------------
 * Frees all resources used by the game, including rendering system and asset manager.
 *
 * Parameters:
 *   renderSys: Pointer to the NGPL_RenderSys to be cleaned up.
 *   assetManager: Pointer to the NGPL_AssetManager to be cleaned up.
 */
void NGPL_CleanUpG(NGPL_RenderSys* renderSys, NGPL_AssetManager* assetManager)
{
    NGPL_DestroyRenderSys(renderSys);
    NGPL_DestroyAssetManager(assetManager);
}

NGPL_EntityPool NGPL_CreateEntityPool(int size)
{
    // Allocate memory for an array of NGPL_Entity pointers
    NGPL_Entity** pool_1 = malloc(size * sizeof(NGPL_Entity*));
    if (pool_1 == NULL)
    {
        printf("Pool malloc failed\n");
    }
    NGPL_EntityPool pool = {pool_1, 0, size};
    return pool;
}

void NGPL_AddToPool(NGPL_EntityPool* pool, NGPL_Entity* entity)
{
    if (pool->count < pool->maxSize)
    {
        pool->pool[pool->count] = entity;
        entity->poolID = pool->count;
        pool->count++;
    } else {
        printf("Pool is full, cannot add more entities.\n");
    }
}

void NGPL_FreePool(NGPL_EntityPool* pool)
{
    free(pool->pool);
}

void NGPL_SetDynamic(NGPL_Entity* entity, bool dynamic)
{
    entity->dynamic = dynamic;
}

void NGPL_SetMass(NGPL_Entity* entity, float mass)
{
    entity->mass = mass;
}

void NGPL_SetSpriteImage(NGPL_Entity e, NGPL_Texture* texture)
{
    e.sprite->image = texture;
}

void NGPL_LoadSetSpriteImage(NGPL_Entity e, Renderer renderer, const char* fp)
{
    NGPL_Texture* texture = NGPL_CreateTexture(renderer, fp);
    e.sprite->image = texture;
}

void NGPL_SetSpriteRectPoints(NGPL_Sprite* sprite)
{
    float TL[] = {(float)sprite->rect.x, sprite->rect.y};
    sprite->rectTopLeft[0] = TL[0];
    sprite->rectTopLeft[1] = TL[1];
    
    float T[] = {(float)sprite->rect.x+sprite->rect.w/2, sprite->rect.y};
    sprite->rectTop[0] = T[0];
    sprite->rectTop[1] = T[1];
    
    float TR[] = {(float)sprite->rect.x+sprite->rect.w, sprite->rect.y};
    sprite->rectTopRight[0] = TR[0];
    sprite->rectTopRight[1] = TR[1];
    
    float ML[] = {(float)sprite->rect.x, sprite->rect.y+sprite->rect.h/2};
    sprite->rectMidLeft[0] = ML[0];
    sprite->rectMidLeft[1] = ML[1];
    
    float MR[] = {(float)sprite->rect.x+sprite->rect.w, sprite->rect.y+sprite->rect.h/2};
    sprite->rectMidRight[0] = MR[0];
    sprite->rectMidRight[1] = MR[1];
    
    float BL[] = {(float)sprite->rect.x, sprite->rect.y+sprite->rect.h};
    sprite->rectBottomLeft[0] = BL[0];
    sprite->rectBottomLeft[1] = BL[1];
    
    float B[] = {(float)sprite->rect.x+sprite->rect.w/2, sprite->rect.y+sprite->rect.h};
    sprite->rectBottom[0] = B[0];
    sprite->rectBottom[1] = B[1];
    
    float BR[] = {(float)sprite->rect.x+sprite->rect.w, sprite->rect.y+sprite->rect.h};
    sprite->rectBottomRight[0] = BR[0];
    sprite->rectBottomRight[1] = BR[1];
}

void NGPL_LogEntityPoolID(NGPL_Entity* e)
{
    if (!e->tag)
    {
        printf("\nEntity PoolID: %d\n",e->poolID);
    } else {
        printf("\n(NGPL_Entity)%s PoolID: %d\n",e->tag,e->poolID);
    }
}

int NGPL_GetEntityPoolID(NGPL_Entity* e)
{
    return e->poolID;
}

void NGPL_SetEntityTag(const char* tag, NGPL_Entity* e)
{
    e->tag = tag;
}


