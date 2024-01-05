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

#ifndef NDL_H
#define NDL_H

#include "NDL_C.h"



NDL_Entity* CreateEntity();

Pool* CreatePool(int poolSize);

void AddToPool(NDL_Entity* e, Pool* pool);

ColliderComponent* CreateColliderComponent(float x, float y, int w, int h);

void AddSpriteComponent(NDL_Entity *entity, Vector2 size, NDL_Color spriteColor);

void AddColliderComponent(NDL_Entity* entity, Vector2 size, NDL_Color colliderColor);

void RemComponent(NDL_Entity* e, Components component);

bool HasComponent(NDL_Entity* e, Components component);

void AddSpriteTexture(Renderer ren, NDL_Entity* e, const char* fp);

void SetEntityTag(NDL_Entity* entity, const char* tag);

void SetEntityDynamic(NDL_Entity* entity, bool set);

void RemEntityTag(NDL_Entity* entity);

void RemSpriteComponent(NDL_Entity* entity);

void RemColliderComponent(NDL_Entity* entity);

void UpdateSystem(RenderSystem* renSys, PhysicsSystem* physicsSystem, float deltaTime, int UPF);

void SetPhysicsSystemGravity(PhysicsSystem* phys, float gravity);

void SetPhysicsSystemFrictionX(PhysicsSystem* phys, float frictionX);

void SetPhysicsSystemFrictionY(PhysicsSystem* phys, float frictionY);

bool EnablePhysicsSystemFrictionX(PhysicsSystem* phys, bool frictionX);

bool EnablePhysicsSystemFrictionY(PhysicsSystem* phys, bool frictionY);

/*
 * Function: NDL_Test
 * ----------------------------
 * Returns a test message if NDL is initialize correctly.
 *
 * Returns: 
 *   A character array.
 */
char* NDL_Test();

/*
 * Function: NDL_Init
 * ---------------------------
 * Attempts to initialize the core components of NDL (SDL2,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void.
 */
void NDL_Init();

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
 * Function: NDL_InitSubSystem
 * ---------------------------
 * Attempts to initialize the SubSystem passed in.
 * Prints a success message if components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *   Void.
 */
int NDL_InitSubSystem(Uint32 flags);

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
int NDL_GetKey(Event event);

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
bool NDL_GetEvent(Event* event, Window window, Renderer renderer);

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
void NDL_CleanUp(Renderer renderer, Window window);

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
const Uint8* NDL_GetKeyState(int* numKeys);

#include "NDL_P.h"
#include "NDL_G.h"
#include "NDL_M.h"
#include "NDL_U.h"
#include "NDL_A.h"

#endif
