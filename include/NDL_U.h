/*
  Nebula's Graphics Programming Library 
  2023-2023 Setoichi Yumaden <setoichi.dev@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef NDL_U_H
#define NDL_U_H
#include "NDL.h"

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
NDL_Clock NDL_CreateClock(int maxFPS);

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
void NDL_InitClock(NDL_Clock* clock, int maxFPS);

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
void NDL_UpdateClock(NDL_Clock* clock);

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
Uint32 NDL_GetTicks(NDL_Clock* clock);

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
float NDL_GetFPS(NDL_Clock* clock);

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
float NDL_GetDeltaTime(NDL_Clock* clock);

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
void NDL_CapFPS(NDL_Clock* clock);

int NDL_IsMouseHover(int mouseX, int mouseY, int pointX, int pointY, int size);

char* NDL_ReadFileToString(const char* filename);

Vector2F NDL_GetMouseVectorF();

bool NDL_IsMouseOverRigidBody(NDL_ColliderComponent* rb);

bool NDL_IsMouseAtPoint(int x, int y);

Vector2 NDL_GetWindowSize(SDL_Window* window);

NDL_Camera* NDL_CreateCamera(Vector2F position, float panSpeed, float interpolation);

// void NDL_CenterCameraOnEntity(Window win, NDL_Camera* cam, NDL_Entity* entity, float deltaTime);

// void NDL_BoxCamera(NDL_Camera* cam, NDL_Entity* entity, SDL_Rect box, float deltaTime);

// void NDL_PanCamera(NDL_Camera* cam, Vector2F targetPosition, float interpolation, float deltaTime);

/*
 * Function: NDL_OpenController
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
Controller NDL_OpenController();

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
NDL_PlayerActions NDL_GetPlayerActions();

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
void NDL_SetKeyBinds(SDL_Scancode moveUp, SDL_Scancode moveDown, SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode attack, SDL_Scancode menu);

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
NDL_Texture* NDL_CreateTexture(Renderer renderer, const char* fp);

// void NDL_LayoutMapData(NDL_PSpace* space, NDL_PoolE* pool, Renderer ren, const char* mapDataPath, Vector2 tileSize);



#endif