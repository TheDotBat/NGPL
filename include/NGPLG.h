#ifndef NGPLG_H
#define NGPLG_H
#include "NGPL.h"
#include "NGPL_Graphics.h"

/*
 * Struct: Tile
 * ------------
 * Represents a tile with a specific position, size, and color.
 *
 * This structure is used to define individual tiles in a game. Each tile
 * is represented by a rectangle (using the Rect type)
 * and a color. Tiles are commonly used in tile-based game environments, like
 * maps or backgrounds, and can be used for both rendering and collision detection.
 *
 * Members:
 *   rect: A Rect representing the position and size of the tile.
 *   color: An array of 4 integers representing the RGBA color of the tile.
 */
typedef struct Tile {
    Rect rect;
    int color[4];
} Tile;

typedef struct NGPL_Sprite {
    int color[4];
    NGPL_Texture* texture;
    Rect rect;
    int renderLayer;
} NGPL_Sprite;

/*
 * Struct: Entity
 * --------------
 * Represents a game object with position, size, velocity, and color.
 *
 * This structure defines a basic game object in 2D space, including its position,
 * size, velocity, and color. Used for representing and manipulating entities in the game.
 *
 * Members:
 *   position: A Vector2D representing the object's position in 2D space.
 *   size: A Vector2D representing the object's size.
 *   velocity: A Vector2D representing the object's velocity.
 *   color: An array of 4 integers representing the RGBA color of the object.
 */
typedef struct NGPL_Entity {
    Vector2D size;
    Vector2D position;
    Vector2D velocity;
    NGPL_Sprite* sprite;
} NGPL_Entity;

typedef struct NGPL_TextureCacheEntry {
    char key[MAX_CACHE_KEY_SIZE];
    NGPL_Texture* texture;
    int frequency;
} NGPL_TextureCacheEntry;

typedef struct NGPL_TextureCache {
    NGPL_TextureCacheEntry* entries;
    int size;
    int maxSize;
} NGPL_TextureCache;

typedef struct NGPL_AssetManager {
    NGPL_TextureCache *textureCache;
} NGPL_AssetManager;

typedef struct NGPL_Renderer {
    NGPL_Entity** entities;
    int entityCount;
    int capacity;
    Renderer sdlRenderer;
    Rect viewport;  // Defines the visible area
} NGPL_Renderer;

/*
 * Enum: PlayerActions
 * --------------------
 * Represents the various actions a player can perform in the game.
 *
 * This enumeration defines a set of bitwise flags corresponding to different player actions.
 * These can be combined using a bitwise OR to represent multiple actions being performed
 * simultaneously. This approach allows for efficient checking and updating of player states.
 *
 * Members:
 *   PLAYER_ACTION_NONE: Represents no action being performed (0).
 *   PLAYER_ACTION_MOVE_LEFT: Represents the action of moving left (0001 in binary).
 *   PLAYER_ACTION_MOVE_RIGHT: Represents the action of moving right (0010 in binary).
 *   PLAYER_ACTION_JUMP: Represents the action of jumping (0100 in binary).
 *   PLAYER_ACTION_MENU: Represents the action of opening the menu (1000 in binary).
 */
typedef enum PlayerActions{
    PLAYER_ACTION_NONE = 0,
    PLAYER_ACTION_MOVE_LEFT = 1 << 0, // 0001
    PLAYER_ACTION_MOVE_RIGHT = 1 << 1, // 0010
    PLAYER_ACTION_JUMP = 1 << 2, // 0100
    PLAYER_ACTION_MENU = 1 << 3, // 1000
} PlayerActions;

/*
 * Struct: KeyBinds
 * ----------------
 * Holds the SDL scancodes for various key bindings used in the game.
 *
 * This structure is used to map SDL scancodes to specific actions within the game,
 * such as moving left or right, jumping, or opening the menu. These bindings can be
 * customized and are used by the game to interpret player input.
 *
 * Members:
 *   moveLeft: SDL_Scancode representing the key for moving the player left.
 *   moveRight: SDL_Scancode representing the key for moving the player right.
 *   jump: SDL_Scancode representing the key for making the player jump.
 *   menu: SDL_Scancode representing the key for opening the game menu.
 */
typedef struct Keybinds{
    SDL_Scancode moveLeft;
    SDL_Scancode moveRight;
    SDL_Scancode jump;
    SDL_Scancode menu;
} KeyBinds;
KeyBinds keyBinds;

/*
 * Function: NGPL_Init
 * ---------------------------
 * Attempts to initialize the core components of NGPL (SDL2,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void
 */
void NGPL_InitG();

/*
 * Function: NGPL_OpenController
 * -----------------------------------------
 * Initializes the SDL game controller subsystem and opens the first available controller.
 *
 * This function will attempt to find and open the first connected game controller.
 * It initializes the SDL game controller subsystem if not already initialized.
 *
 * Returns:
 *   A pointer to an SDL_GameController object if a controller is successfully opened,
 *   NULL otherwise.
 */
Controller NGPL_OpenController();

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
PlayerActions NGPL_GetPlayerActions();

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
void NGPL_SetKeyBinds(SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode menu);

/*
 * Function: NGPL_CreateObject
 * ---------------------------
 * Creates and initializes an Entity structure.
 *
 * This function sets up an Entity with specified position, size, and default
 * values for velocity and color. It's used for creating new game objects.
 *
 * Parameters:
 *   position: An array of 2 floats representing the initial position of the object.
 *   size: An array of 2 floats representing the size of the object.
 *
 * Returns:
 *   Entity: The newly created and initialized game object.
 */
NGPL_Entity* NGPL_CreateEntity(int color[4], float size[2], float position[2], int renderLayer, Renderer renderer, NGPL_Sprite* sprite);

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
NGPL_Texture* NGPL_CreateTexture(Renderer renderer, int width, int height, const char* fp);

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
void NGPL_DestroyTexture(NGPL_Texture* texture);

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
NGPL_TextureCache* NGPL_CreateTextureCache(int maxSize);

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

void NGPL_DestroyTextureCache(NGPL_TextureCache* cache);

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
NGPL_Texture* NGPL_TextureCacheGet(NGPL_TextureCache* cache, const char* key);

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
int NGPL_TextureCachePut(NGPL_TextureCache* cache, const char* key, NGPL_Texture* texture);

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
NGPL_AssetManager* NGPL_CreateAssetManager(int cacheSize);

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
int NGPL_LoadTextureAsset(NGPL_AssetManager* manager, Renderer renderer, const char* assetKey, const char* filePath);

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
NGPL_Texture* NGPL_GetTextureAsset(NGPL_AssetManager* manager, const char* assetKey);

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
void NGPL_DestroyAssetManager(NGPL_AssetManager* manager);

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
NGPL_Sprite* NGPL_CreateSprite(NGPL_Texture* texture, float position[2], float size[2], int rendererLayer, Renderer renderer);

/*
 * Function: NGPL_CreateRenderSys
 * ------------------------------
 * Initializes and creates a rendering system for NGPL_Sprite(s).
 *
 * Parameters:
 *   sdlRenderer: Pointer to the SDL renderer.
 *
 * Returns:
 *   NGPL_Renderer*: Pointer to the newly created rendering system.
 */
NGPL_Renderer* NGPL_CreateRenderSys(Renderer sdlRenderer);

/*
 * Function: NGPL_DestroyRenderSys
 * -------------------------------
 * Cleans up and frees resources allocated for a rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_Renderer to be destroyed.
 */
void NGPL_DestroyRenderSys(NGPL_Renderer* renderer);

/*
 * Function: NGPL_RSAddEntity
 * --------------------------
 * Adds a sprite struct from a NGPL_Sprite pointer passed in, to the rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_Renderer.
 *   texture: Pointer to the SDL_Texture to be used for the sprite.
 *   rect: SDL_Rect structure defining the sprite's position and size.
 *   layer: Integer specifying the rendering layer of the sprite.
 */
void NGPL_RSAddEntity(NGPL_Renderer* renderer, NGPL_Entity* entity);

/*
 * Function: NGPL_RSRemoveEntity
 * -----------------------------
 * Removes a sprite from the rendering system.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_Renderer.
 *   texture: Pointer to the SDL_Texture of the sprite to be removed.
 */
void NGPL_RSRemoveEntity(NGPL_Renderer* renderer, NGPL_Texture* texture);

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
int NGPL_RSCompareEntities(const void* a, const void* b);

/*
 * Function: NGPL_RSSortEntities
 * ----------------------------
 * Sorts entities in a rendering system based on their layer.
 * * This function is used within NGPL_RSRender(). There really shouldn't be a need for you to call it again.
 * Parameters:
 *   renderer: Pointer to the NGPL_Renderer.
 */
void NGPL_RSSortEntities(NGPL_Renderer* renderer);

/*
 * Function: NGPL_RSRender
 * -----------------------
 * Renders all entities in the rendering system.
 * If an Entity's sprite->texture is NULL then it will render that sprite's rect.
 *
 * Parameters:
 *   renderer: Pointer to the NGPL_Renderer.
 */
void NGPL_RSRender(NGPL_Renderer* renderer, int clearColor[4]);

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
void NGPL_DestroySprite(NGPL_Sprite* sprite);

/*
 * Function: NGPL_GameCleanUp
 * --------------------------
 * Frees all resources used by the game, including rendering system and asset manager.
 *
 * Parameters:
 *   renderSys: Pointer to the NGPL_Renderer to be cleaned up.
 *   assetManager: Pointer to the NGPL_AssetManager to be cleaned up.
 */
void NGPL_CleanUpG(NGPL_Renderer* renderSys, NGPL_AssetManager* assetManager);

/*
 * Function: NGPL_SetEntityTexture
 * -------------------------------
 * Associates a texture with a given entity by setting the texture of the entity's sprite.
 * This function is used to define or change the visual representation of an entity.
 *
 * Parameters:
 *   entity: Pointer to the NGPL_Entity for which the texture is to be set.
 *   texture: Pointer to the NGPL_Texture to be associated with the entity's sprite.
 *
 * Note:
 *   This function does not handle the memory management of the texture. It only links
 *   the texture to the entity's sprite.
 */
void NGPL_SetEntityTexture(NGPL_Entity* entity, NGPL_Texture* texture);

/*
 * Function: NGPL_SetSpriteTexture
 * --------------------------------
 * Assigns a texture to a sprite. This function is used to define or change the visual
 * representation of a sprite.
 *
 * Parameters:
 *   sprite: Pointer to the NGPL_Sprite to which the texture is to be assigned.
 *   texture: Pointer to the NGPL_Texture that will be used as the sprite's texture.
 *
 * Note:
 *   Like NGPL_SetEntityTexture, this function links the texture to the sprite but
 *   does not take ownership of the texture's memory.
 */
void NGPL_SetSpriteTexture(NGPL_Sprite* sprite, NGPL_Texture* texture);

#endif