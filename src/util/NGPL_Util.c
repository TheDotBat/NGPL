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


