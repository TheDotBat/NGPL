#include "../../include/NGPL_Util.h"


/*
 * Function: NGPL_CreateClock
 * -----------------------------------------
 * Creates and initializes a new Clock object with a specified maximum FPS.
 *
 * This function constructs a Clock object, setting its maximum FPS to the provided value.
 * It calls NGPL_InitClock internally to initialize the Clock's fields.
 *
 * Parameters:
 *   maxFPS: The maximum frames per second (FPS) limit for the game clock.
 *
 * Returns:
 *   A fully initialized Clock object.
 */
Clock NGPL_CreateClock(int maxFPS)
{
    Clock clock;
    NGPL_InitClock(&clock, maxFPS);
    return clock;
}

/*
 * Function: NGPL_InitClock
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
void NGPL_InitClock(Clock* clock, int maxFPS)
{
    clock->FPS = 0.0f;
    clock->maxFPS = maxFPS;
    clock->TPF = 1000.0f/maxFPS;
    clock->deltaTime = 0.0f;
    clock->frameCount = 0.0f;
    clock->lastTime = NGPL_GetTicks(clock);
    clock->currentTime = clock->lastTime;
}

/*
 * Function: NGPL_UpdateClock
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
void NGPL_UpdateClock(Clock* clock) {
    clock->currentTime = NGPL_GetTicks(clock);
    clock->deltaTime = (clock->currentTime - clock->lastTime) / 1000.0f;
    clock->frameCount++;

    clock->FPS = clock->frameCount / ((clock->currentTime - clock->lastTime) / 1000.0f);
    clock->lastTime = clock->currentTime;
    clock->frameCount = 0;
}

/*
 * Function: NGPL_GetTicks
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
Uint32 NGPL_GetTicks(Clock* clock)
{
    return SDL_GetTicks();
}

/*
 * Function: NGPL_GetFPS
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
float NGPL_GetFPS(Clock* clock)
{
    return clock->FPS;
}

/*
 * Function: NGPL_GetDeltaTime
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
float NGPL_GetDeltaTime(Clock* clock) {
    return clock->deltaTime;
}

/*
 * Function: NGPL_CapFPS
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
void NGPL_CapFPS(Clock* clock) {
    Uint32 frameTime = NGPL_GetTicks(clock) - clock->currentTime;
    if (frameTime < clock->TPF) {
        SDL_Delay((Uint32)clock->TPF - frameTime);
    }
}

int NGPL_IsMouseHover(int mouseX, int mouseY, int pointX, int pointY, int size)
{
    return (mouseX >= pointX - size/2 && mouseX <= pointX + size/2 &&
            mouseY >= pointY - size/2 && mouseY <= pointY + size/2);
}

NGPL_PoolE* NGPL_CreatePool(int maxSize)
{
    NGPL_PoolE* pool = malloc(sizeof(NGPL_PoolE));

    pool->entities = malloc(sizeof(NGPL_Entity)*maxSize);
    if (pool->entities == NULL)
    {
        free(pool);
        return NULL;
    }

    pool->size = 0;
    pool->maxSize = maxSize;
    for (int i = 0; i < maxSize; i++)
    {
        pool->entities[i] = malloc(sizeof(NGPL_Entity));
    }

    return pool;
}

void NGPL_AddToPool(NGPL_Entity* e, NGPL_PoolE* pool)
{
    if (pool->size >= pool->maxSize)
    {
        printf("This Pool is full, cannot add more entities\n");
        return;
    }
    pool->entities[pool->size] = e;
    pool->size++;
}

char* NGPL_ReadFileToString(const char* filename)
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

Vector2F NGPL_GetMouseVectorF()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    Vector2F mousePos = {(float)x, (float)y};
    return mousePos;
}

bool NGPL_IsMouseOverSprite(NGPL_Entity* entity)
{
    Vector2F mousePos = NGPL_GetMouseVectorF();
    SDL_Point mousePoint = {(int)mousePos.x, (int)mousePos.y};
    SDL_Rect spriteRect = {entity->sprite.imgRect.x, entity->sprite.imgRect.y, entity->sprite.imgRect.w, entity->sprite.imgRect.h};

    return SDL_PointInRect(&mousePoint, &spriteRect);
}

bool NGPL_IsMouseOverRigidBody(NGPL_RigidBody* rb)
{
    Vector2F mousePos = NGPL_GetMouseVectorF();
    SDL_Point mousePoint = {(int)mousePos.x, (int)mousePos.y};
    SDL_Rect rigidBodyRect = {rb->r.x, rb->r.y, rb->r.w, rb->r.h};

    return SDL_PointInRect(&mousePoint, &rigidBodyRect);
}

bool NGPL_IsMouseAtPoint(int x, int y)
{
    Vector2F mousePos = NGPL_GetMouseVectorF();
    return (mousePos.x == x && mousePos.y == y);
}

Vector2 NGPL_GetWindowSize(SDL_Window* window)
{
    Vector2 size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return size;
}

NGPL_Camera* NGPL_CreateCamera(Vector2F position, float panSpeed, float interpolation)
{
    NGPL_Camera* cam = malloc(sizeof(NGPL_Camera));
    if (cam == NULL) {
        fprintf(stderr, "Failed to allocate memory for NGPL_Camera\n");
        return NULL;
    }
    cam->cameraSpeed = panSpeed;
    cam->scrollInterpolation = interpolation;
    cam->position = position;
    return cam;
}

void NGPL_CenterCameraOnEntity(Window win, NGPL_Camera* cam, NGPL_Entity* entity, float deltaTime)
{
    Vector2F targetCenter = {entity->position.x + entity->size.x / 2, entity->position.y + entity->size.y / 2};
    Vector2F screenSize = (Vector2F){1400.0,600.0};
    // Vector2F screenSize = (Vector2F){NGPL_GetWindowSize(win).x, NGPL_GetWindowSize(win).y};
    Vector2F desiredScroll = {targetCenter.x - screenSize.x / 2, targetCenter.y - screenSize.y / 2};

    cam->position.x += (desiredScroll.x - cam->position.x) * cam->cameraSpeed * deltaTime / cam->scrollInterpolation;
    cam->position.y += (desiredScroll.y - cam->position.y) * cam->cameraSpeed * deltaTime / cam->scrollInterpolation;
}

void NGPL_BoxCamera(NGPL_Camera* cam, NGPL_Entity* entity, SDL_Rect box, float deltaTime)
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

void NGPL_PanCamera(NGPL_Camera* cam, Vector2F targetPosition, float interpolation, float deltaTime)
{
    Vector2F interpolatedPosition;

    interpolatedPosition.x = cam->position.x + (targetPosition.x - cam->position.x) * interpolation * deltaTime;
    interpolatedPosition.y = cam->position.y + (targetPosition.y - cam->position.y) * interpolation * deltaTime;

    cam->position = interpolatedPosition;
}
