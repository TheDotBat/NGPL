#include "../../include/NDL_U.h"

Keybinds keybinds;

/*
 * Function: NDL_CreateClock
 * -----------------------------------------
 * Creates and initializes a new Clock object with a specified maximum FPS.
 *
 * This function constructs a Clock object, setting its maximum FPS to the provided value.
 * It calls NDL_InitClock internally to initialize the Clock's fields.
 *
 * Parameters:
 *   maxFPS: The maximum frames per second (FPS) limit for the game clock.
 *
 * Returns:
 *   A fully initialized Clock object.
 */
NDL_Clock NDL_CreateClock(int maxFPS)
{
    NDL_Clock clock;
    NDL_InitClock(&clock, maxFPS);
    return clock;
}

/*
 * Function: NDL_InitClock
 * -----------------------------------------
 * Initializes a Clock object with a specific maximum FPS.
 *
 * This function sets up the initial state of the Clock, including its maximum FPS.
 * It can be used to reset the clock's state at any time.
 *
 * Parameters:
 *   clock: A pointer to the Clock object to initialize.
 *   maxFPS: The maximum frames per second (FPS) limit for the game clock.
 *
 * Returns:
 *   Void.
 */
void NDL_InitClock(NDL_Clock* clock, int maxFPS)
{
    clock->FPS = 0.0f;
    clock->maxFPS = maxFPS;
    clock->TPF = 1000.0f/maxFPS;
    clock->deltaTime = 0.0f;
    clock->frameCount = 0.0f;
    clock->lastTime = NDL_GetTicks(clock);
    clock->currentTime = clock->lastTime;
}

/*
 * Function: NDL_UpdateClock
 * -----------------------------------------
 * Updates the Clock object each frame to track time and calculate FPS.
 *
 * This function should be called every frame in the game loop.
 * It updates the deltaTime field in seconds and recalculates the FPS if necessary.
 *
 * Parameters:
 *   clock: A pointer to the Clock object to update.
 *
 * Returns:
 *   Void.
 */
void NDL_UpdateClock(NDL_Clock* clock) {
    clock->currentTime = NDL_GetTicks(clock);
    clock->deltaTime = (clock->currentTime - clock->lastTime) / 1000.0f;
    clock->frameCount++;

    clock->FPS = clock->frameCount / ((clock->currentTime - clock->lastTime) / 1000.0f);
    clock->lastTime = clock->currentTime;
    clock->frameCount = 0;
}

/*
 * Function: NDL_GetTicks
 * -----------------------------------------
 * Retrieves the current time in milliseconds since the SDL library was initialized.
 *
 * This function is a wrapper around SDL_GetTicks64, providing the time
 * since the SDL library initialization.
 *
 * Parameters:
 *   clock: A pointer to the Clock object (not directly used in this function).
 *
 * Returns:
 *   An unsigned 32-bit integer representing the time in milliseconds.
 */
Uint32 NDL_GetTicks(NDL_Clock* clock)
{
    return SDL_GetTicks();
}

/*
 * Function: NDL_GetFPS
 * -----------------------------------------
 * Retrieves the current calculated frames per second (FPS) from the Clock object.
 *
 * This function accesses the FPS field of the Clock struct, providing the
 * latest calculated FPS value.
 *
 * Parameters:
 *   clock: A pointer to the Clock object from which to retrieve the FPS.
 *
 * Returns:
 *   A floating-point value representing the current FPS.
 */
float NDL_GetFPS(NDL_Clock* clock)
{
    return clock->FPS;
}

/*
 * Function: NDL_GetDeltaTime
 * -----------------------------------------
 * Retrieves the time elapsed in seconds since the last frame.
 *
 * This function is useful for ensuring time-based calculations are frame rate independent.
 * It accesses the deltaTime field of the Clock struct.
 *
 * Parameters:
 *   clock: A pointer to the Clock object from which to retrieve the delta time.
 *
 * Returns:
 *   A floating-point value representing the delta time in seconds.
 */
float NDL_GetDeltaTime(NDL_Clock* clock) {
    return clock->deltaTime;
}

/*
 * Function: NDL_CapFPS
 * -----------------------------------------
 * Delays the next frame to cap the frame rate of your application at a specific maximum FPS.
 * 
 * This function calculates the time taken for the current frame to process (frameTime) and compares it 
 * with the target time per frame (TPF) based on the maximum FPS set in the Clock structure. If the 
 * current frame processing time is less than the target, the function uses SDL_Delay to wait for the 
 * remaining time, effectively capping the frame rate to the desired maximum FPS.
 *
 * Parameters:
 *   clock: A pointer to the Clock object, which contains timing information and settings for FPS cap.
 *
 * Note:
 *   The Clock object must be properly initialized and updated before calling this function. It relies 
 *   on the current time, TPF (time per frame), and other settings stored in the Clock object.
 *
 * Returns:
 *   Void.
 */
void NDL_CapFPS(NDL_Clock* clock) {
    Uint32 frameTime = NDL_GetTicks(clock) - clock->currentTime;
    if (frameTime < clock->TPF) {
        SDL_Delay((Uint32)clock->TPF - frameTime);
    }
}

int NDL_IsMouseHover(int mouseX, int mouseY, int pointX, int pointY, int size)
{
    return (mouseX >= pointX - size/2 && mouseX <= pointX + size/2 &&
            mouseY >= pointY - size/2 && mouseY <= pointY + size/2);
}

char* NDL_ReadFileToString(const char* filename)
{
    FILE* file = fopen(filename, "rb"); // Open the file in binary mode
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file); // Go back to the start of the file

    // Allocate memory for the file content
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the string
    buffer[fileSize] = '\0';

    // Close the file and return the buffer
    fclose(file);
    return buffer;
}

Vector2F NDL_GetMouseVectorF()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Vector2F mousePos = {(float)x, (float)y};
    return mousePos;
}

bool NDL_IsMouseOverRigidBody(NDL_ColliderComponent* rb)
{
    Vector2F mousePos = NDL_GetMouseVectorF();
    SDL_Point mousePoint = {(int)mousePos.x, (int)mousePos.y};
    SDL_Rect rigidBodyRect = {rb->r.x, rb->r.y, rb->r.w, rb->r.h};

    return SDL_PointInRect(&mousePoint, &rigidBodyRect);
}

bool NDL_IsMouseAtPoint(int x, int y)
{
    Vector2F mousePos = NDL_GetMouseVectorF();
    return (mousePos.x == x && mousePos.y == y);
}

Vector2 NDL_GetWindowSize(SDL_Window* window)
{
    Vector2 size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return size;
}

NDL_Camera* NDL_CreateCamera(Vector2F position, float panSpeed, float interpolation)
{
    NDL_Camera* cam = malloc(sizeof(NDL_Camera));
    if (cam == NULL) {
        fprintf(stderr, "Failed to allocate memory for NDL_Camera\n");
        return NULL;
    }
    cam->cameraSpeed = panSpeed;
    cam->scrollInterpolation = interpolation;
    cam->position = position;
    return cam;
}

void NDL_CenterCameraOnEntity(Window win, NDL_Camera* cam, NDL_Entity* entity, float deltaTime)
{
    Vector2F targetCenter = {entity->position.x + entity->sprite->imageRect.w / 2, entity->position.y + entity->sprite->imageRect.h / 2};
    Vector2F screenSize = (Vector2F){NDL_GetWindowSize(win).x, NDL_GetWindowSize(win).y};
    Vector2F desiredScroll = {targetCenter.x - screenSize.x / 2, targetCenter.y - screenSize.y / 2};

    cam->position.x += (desiredScroll.x - cam->position.x) * cam->cameraSpeed * deltaTime * cam->scrollInterpolation;
    cam->position.y += (desiredScroll.y - cam->position.y) * cam->cameraSpeed * deltaTime * cam->scrollInterpolation;
}

void NDL_BoxCamera(NDL_Camera* cam, NDL_Entity* entity, SDL_Rect box, float deltaTime)
{
    if (entity->position.x < cam->position.x + box.x) {
        cam->position.x = entity->position.x - box.x;
    } else if (entity->position.x > cam->position.x + box.x + box.w) {
        cam->position.x = entity->position.x - box.x - box.w;
    }

    if (entity->position.y < cam->position.y + box.y) {
        cam->position.y = entity->position.y - box.y;
    } else if (entity->position.y > cam->position.y + box.y + box.h) {
        cam->position.y = entity->position.y - box.y - box.h;
    }
}

void NDL_PanCamera(NDL_Camera* cam, Vector2F targetPosition, float interpolation, float deltaTime)
{
    Vector2F interpolatedPosition;

    interpolatedPosition.x = cam->position.x + (targetPosition.x - cam->position.x) * interpolation * deltaTime;
    interpolatedPosition.y = cam->position.y + (targetPosition.y - cam->position.y) * interpolation * deltaTime;

    cam->position = interpolatedPosition;
}

/*
 * Function: NDL_OpenController
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
Controller NDL_OpenController() 
{
    if (NDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) 
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
 * Function: NDL_GetPlayerActions
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
NDL_PlayerActions NDL_GetPlayerActions()
{
    const Uint8* state = NDL_GetKeyState(NULL);
    NDL_PlayerActions actions = PLAYER_ACTION_NONE;

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
 * Function: NDL_SetKeyBinds
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
void NDL_SetKeyBinds(SDL_Scancode moveUp, SDL_Scancode moveDown, SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode attack, SDL_Scancode menu) 
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
 * Function: NDL_CreateTexture
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
 *   NDL_Texture*: Pointer to the created SDL texture.
 */
NDL_Texture* NDL_CreateTexture(Renderer renderer, const char* fp)
{
    if (!fp)
    {
        NDL_Texture* texture = IMG_LoadTexture(renderer, "..\\..\\common\\txtrDefault.png");
        return texture;
    } else {
        NDL_Texture* texture = IMG_LoadTexture(renderer, fp);
        return texture;
    }
}

// void NDL_LayoutMapData(NDL_PSpace* space, NDL_PoolE* pool, Renderer ren, const char* mapDataPath, Vector2 tileSize)
// {
//     // Read the JSON file into a string
//     char* jsonContent = NDL_ReadFileToString(mapDataPath); // Implement this function to read file content
//     if (jsonContent == NULL) {
//         printf("Error reading JSON file\n");
//         return;
//     }
// 
//     // Parse the JSON content
//     cJSON* root = cJSON_Parse(jsonContent);
//     if (root == NULL) {
//         printf("Error parsing JSON\n");
//         free(jsonContent);
//         return;
//     }
// 
//     // Iterate over each tile in the JSON array
//     cJSON* tiles = cJSON_GetObjectItemCaseSensitive(root, "tiles");
//     cJSON* tile;
//     cJSON_ArrayForEach(tile, tiles) {
//         cJSON* position = cJSON_GetObjectItemCaseSensitive(tile, "position");
//         cJSON* imagePath = cJSON_GetObjectItemCaseSensitive(tile, "imagePath"); 
//         cJSON* tileType = cJSON_GetObjectItemCaseSensitive(tile, "type"); 
// 
//         int x = cJSON_GetObjectItemCaseSensitive(position, "x")->valueint;
//         int y = cJSON_GetObjectItemCaseSensitive(position, "y")->valueint;
//         const char* imagePathStr = imagePath->valuestring;
//         const char* tileTypeStr = tileType->valuestring;
//         bool isDynamic = !strcmp(tileTypeStr, "dynamic") ? true : false; // Check tile type
//         printf("Image Path Retrieved: %s\n",imagePathStr);
// 
//         // Create the tile entity
//         NDL_Entity* tileEntity = malloc(sizeof(NDL_Entity));
//         if (tileEntity == NULL) {
//             continue; // Handle memory allocation failure
//         }
// 
//         *tileEntity = NDL_CreateEntity(space, (Vector2F){x*tileSize.x, y*tileSize.y}, (Vector2){tileSize.x, tileSize.y}, (NDL_Color){0, 0, 255, 255});
//         tileEntity->sprite.image = NDL_CreateTexture(ren, imagePathStr);
//         NDL_CreateEntityRigidBody(space, tileEntity, 30.0, tileEntity->position, (Vector2){tileSize.x, tileSize.y});
//         if (isDynamic) NDL_SetRigidBodyDynamic(tileEntity->rb, isDynamic);
//         NDL_SetEntityImageOffsetX(tileEntity, 0);
//         NDL_SetEntityImageOffsetY(tileEntity, 0);
//         NDL_EntityUpdate(tileEntity);
//         NDL_AddToPoolE(tileEntity, pool);
//     }
//     // Clean up
//     cJSON_Delete(root);
//     free(jsonContent);
// }
// 
// 
// 
// 
// 
