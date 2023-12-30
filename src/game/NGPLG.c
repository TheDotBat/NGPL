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

    if (state[keyBinds.moveLeft]) {
        actions |= PLAYER_ACTION_MOVE_LEFT;
    }
    if (state[keyBinds.moveRight]) {
        actions |= PLAYER_ACTION_MOVE_RIGHT;
    }
    if (state[keyBinds.jump]) {
        actions |= PLAYER_ACTION_JUMP;
    }
    if (state[keyBinds.menu]) {
        actions |= PLAYER_ACTION_MENU;
    }
    if (state[keyBinds.moveUp]) {
        actions |= PLAYER_ACTION_MOVE_UP;
    }
    if (state[keyBinds.moveDown]) {
        actions |= PLAYER_ACTION_MOVE_DOWN;
    }
    if (state[keyBinds.attack]) {
        actions |= PLAYER_ACTION_ATTACK;
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
void NGPL_SetKeyBinds(SDL_Scancode moveUp, SDL_Scancode moveDown, SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode attack, SDL_Scancode menu) 
{
    keyBinds.moveUp = moveUp;
    keyBinds.moveDown = moveDown;
    keyBinds.moveLeft = moveLeft;
    keyBinds.moveRight = moveRight;
    keyBinds.jump = jump;
    keyBinds.menu = menu;
    keyBinds.attack = attack;
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
void NGPL_CreateSprite(NGPL_Entity* e, Vector2 size, NGPL_Color color)
{
    NGPL_Sprite s;
    s.size = size;
    s.image = NULL;
    s.color = color;
    s.imgRect.w = s.size.x;
    s.imgRect.h = s.size.y;
    s.imgRect.x = e->position.x;
    s.imgRect.y = e->position.y;
    s.imageOffset.x = 0;
    s.imageOffset.y = 0;
    
    e->sprite = s;
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
NGPL_Entity NGPL_CreateEntity(NGPL_PSpace* space, Vector2F position, Vector2 size, NGPL_Color color)
{
    NGPL_Entity e;
    e.rb = NULL;
    e.tag = NULL;
    e.size = size;
    e.position.x = space->bounds.x + position.x;
    e.position.y = space->bounds.y + position.y;
    e.velocity.x = 0.0;
    e.velocity.y = 0.0;
    NGPL_CreateSprite(&e, e.size, color);
    return e;
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

void NGPL_SetEntityTag(const char* tag, NGPL_Entity* e)
{
    e->tag = tag;
}

void NGPL_SetEntityImageOffsetX(NGPL_Entity* e, int offsetX)
{
    e->sprite.imageOffset.x = offsetX;
}

void NGPL_SetEntityImageOffsetY(NGPL_Entity* e, int offsetY)
{
    e->sprite.imageOffset.y = offsetY;
}

void NGPL_LoadSetEntityImage(Renderer ren, NGPL_Entity* e, const char* fp)
{
    e->sprite.image = NGPL_CreateTexture(ren, fp);
}

void NGPL_LayoutMapData(NGPL_PSpace* space, NGPL_PoolE* pool, Renderer ren, const char* mapDataPath, Vector2 tileSize)
{
    // Read the JSON file into a string
    char* jsonContent = NGPL_ReadFileToString(mapDataPath); // Implement this function to read file content
    if (jsonContent == NULL) {
        printf("Error reading JSON file\n");
        return;
    }

    // Parse the JSON content
    cJSON* root = cJSON_Parse(jsonContent);
    if (root == NULL) {
        printf("Error parsing JSON\n");
        free(jsonContent);
        return;
    }

    // Iterate over each tile in the JSON array
    cJSON* tiles = cJSON_GetObjectItemCaseSensitive(root, "tiles");
    cJSON* tile;
    cJSON_ArrayForEach(tile, tiles) {
        cJSON* position = cJSON_GetObjectItemCaseSensitive(tile, "position");
        cJSON* imagePath = cJSON_GetObjectItemCaseSensitive(tile, "imagePath"); 
        cJSON* tileType = cJSON_GetObjectItemCaseSensitive(tile, "type"); 

        int x = cJSON_GetObjectItemCaseSensitive(position, "x")->valueint;
        int y = cJSON_GetObjectItemCaseSensitive(position, "y")->valueint;
        const char* imagePathStr = imagePath->valuestring;
        const char* tileTypeStr = tileType->valuestring;
        bool isDynamic = !strcmp(tileTypeStr, "dynamic") ? true : false; // Check tile type
        printf("Image Path Retrieved: %s\n",imagePathStr);

        // Create the tile entity
        NGPL_Entity* tileEntity = malloc(sizeof(NGPL_Entity));
        if (tileEntity == NULL) {
            continue; // Handle memory allocation failure
        }

        *tileEntity = NGPL_CreateEntity(space, (Vector2F){x*tileSize.x, y*tileSize.y}, (Vector2){tileSize.x, tileSize.y}, (NGPL_Color){0, 0, 255, 255});
        tileEntity->sprite.image = NGPL_CreateTexture(ren, imagePathStr);
        NGPL_CreateEntityRigidBody(space, true, tileEntity, 30.0, tileEntity->position, (Vector2){tileSize.x, tileSize.y});
        if (isDynamic) 
        {
            NGPL_SetEntityImageOffsetX(tileEntity, 0);
            NGPL_SetEntityImageOffsetY(tileEntity, 0);
            NGPL_EntityUpdate(tileEntity);
        } else {
            NGPL_SetRigidBodyDynamic(tileEntity->rb, false);
            NGPL_SetEntityImageOffsetX(tileEntity, 0);
            NGPL_SetEntityImageOffsetY(tileEntity, 0);
            NGPL_EntityUpdate(tileEntity);
        }
        NGPL_AddToPoolE(tileEntity, pool);
    }
    // Clean up
    cJSON_Delete(root);
    free(jsonContent);
}




