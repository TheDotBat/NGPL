#ifndef NGPL_CORE_H
#define NGPL_CORE_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//#include "SDL.h"
#include "SDL_image.h"
#undef main

#define MAX_CACHE_KEY_SIZE 50
#define INITIAL_RENDER_SYS_CAPACITY 10

#define NGPL_KEY_UP_ARROW SDL_SCANCODE_UP
#define NGPL_KEY_DOWN_ARROW SDL_SCANCODE_DOWN
#define NGPL_KEY_LEFT_ARROW SDL_SCANCODE_LEFT
#define NGPL_KEY_RIGHT_ARROW SDL_SCANCODE_RIGHT

#define NGPL_KEY_A SDL_SCANCODE_A
#define NGPL_KEY_B SDL_SCANCODE_B
#define NGPL_KEY_C SDL_SCANCODE_C
#define NGPL_KEY_D SDL_SCANCODE_D
#define NGPL_KEY_E SDL_SCANCODE_E
#define NGPL_KEY_F SDL_SCANCODE_F
#define NGPL_KEY_G SDL_SCANCODE_G
#define NGPL_KEY_H SDL_SCANCODE_H
#define NGPL_KEY_I SDL_SCANCODE_I
#define NGPL_KEY_J SDL_SCANCODE_J
#define NGPL_KEY_K SDL_SCANCODE_K
#define NGPL_KEY_L SDL_SCANCODE_L
#define NGPL_KEY_M SDL_SCANCODE_M
#define NGPL_KEY_N SDL_SCANCODE_N
#define NGPL_KEY_O SDL_SCANCODE_O
#define NGPL_KEY_P SDL_SCANCODE_P
#define NGPL_KEY_Q SDL_SCANCODE_Q
#define NGPL_KEY_R SDL_SCANCODE_R
#define NGPL_KEY_S SDL_SCANCODE_S
#define NGPL_KEY_T SDL_SCANCODE_T
#define NGPL_KEY_U SDL_SCANCODE_U
#define NGPL_KEY_V SDL_SCANCODE_V
#define NGPL_KEY_W SDL_SCANCODE_W
#define NGPL_KEY_X SDL_SCANCODE_X
#define NGPL_KEY_Y SDL_SCANCODE_Y
#define NGPL_KEY_Z SDL_SCANCODE_Z

#define NGPL_KEY_0 SDL_SCANCODE_0
#define NGPL_KEY_1 SDL_SCANCODE_1
#define NGPL_KEY_2 SDL_SCANCODE_2
#define NGPL_KEY_3 SDL_SCANCODE_3
#define NGPL_KEY_4 SDL_SCANCODE_4
#define NGPL_KEY_5 SDL_SCANCODE_5
#define NGPL_KEY_6 SDL_SCANCODE_6
#define NGPL_KEY_7 SDL_SCANCODE_7
#define NGPL_KEY_8 SDL_SCANCODE_8
#define NGPL_KEY_9 SDL_SCANCODE_9

#define NGPL_KEY_SPACE SDL_SCANCODE_SPACE
#define NGPL_KEY_ENTER SDL_SCANCODE_RETURN
#define NGPL_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define NGPL_KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define NGPL_KEY_TAB SDL_SCANCODE_TAB
#define NGPL_KEY_SHIFT SDL_SCANCODE_LSHIFT
#define NGPL_KEY_CTRL SDL_SCANCODE_LCTRL
#define NGPL_KEY_ALT SDL_SCANCODE_LALT
#define NGPL_KEY_RSHIFT SDL_SCANCODE_RSHIFT
#define NGPL_KEY_RCTRL SDL_SCANCODE_RCTRL
#define NGPL_KEY_RALT SDL_SCANCODE_RALT

#define NGPL_KEYUP SDL_KEYUP
#define NGPL_KEYDOWN SDL_KEYDOWN

#define NGPL_CONTROLLER_BUTTON_A SDL_CONTROLLER_BUTTON_A
#define NGPL_CONTROLLER_BUTTON_B SDL_CONTROLLER_BUTTON_B
#define NGPL_CONTROLLER_BUTTON_X SDL_CONTROLLER_BUTTON_X
#define NGPL_CONTROLLER_BUTTON_Y SDL_CONTROLLER_BUTTON_Y
#define NGPL_CONTROLLER_BUTTON_BACK SDL_CONTROLLER_BUTTON_BACK
#define NGPL_CONTROLLER_BUTTON_GUIDE SDL_CONTROLLER_BUTTON_GUIDE
#define NGPL_CONTROLLER_BUTTON_START SDL_CONTROLLER_BUTTON_START
#define NGPL_CONTROLLER_BUTTON_LEFTSTICK SDL_CONTROLLER_BUTTON_LEFTSTICK
#define NGPL_CONTROLLER_BUTTON_RIGHTSTICK SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define NGPL_CONTROLLER_BUTTON_LEFTSHOULDER SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define NGPL_CONTROLLER_BUTTON_RIGHTSHOULDER SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define NGPL_CONTROLLER_BUTTON_DPAD_UP SDL_CONTROLLER_BUTTON_DPAD_UP
#define NGPL_CONTROLLER_BUTTON_DPAD_DOWN SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define NGPL_CONTROLLER_BUTTON_DPAD_LEFT SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define NGPL_CONTROLLER_BUTTON_DPAD_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT

#define NGPL_CONTROLLER_AXIS_LEFTX SDL_CONTROLLER_AXIS_LEFTX
#define NGPL_CONTROLLER_AXIS_LEFTY SDL_CONTROLLER_AXIS_LEFTY
#define NGPL_CONTROLLER_AXIS_RIGHTX SDL_CONTROLLER_AXIS_RIGHTX
#define NGPL_CONTROLLER_AXIS_RIGHTY SDL_CONTROLLER_AXIS_RIGHTY
#define NGPL_CONTROLLER_AXIS_TRIGGERLEFT SDL_CONTROLLER_AXIS_TRIGGERLEFT
#define NGPL_CONTROLLER_AXIS_TRIGGERRIGHT SDL_CONTROLLER_AXIS_TRIGGERRIGHT

#define NGPL_CONTROLLER_BUTTON_DOWN SDL_CONTROLLERBUTTONDOWN
#define NGPL_CONTROLLER_BUTTON_UP SDL_CONTROLLERBUTTONUP
#define NGPL_CONTROLLER_AXIS_MOTION SDL_CONTROLLERAXISMOTION


// CONSTANTS
/*
 * Typedefs: SDL Type Aliases
 * --------------------------
 * These typedefs are aliases for various SDL types, simplifying their usage within the game engine.
 * They provide a more concise way to refer to common SDL structures and pointers.
 *
 * Typedefs:
 *   Rect: An alias for SDL_Rect, which represents a rectangle with position and size.
 *   Window: An alias for SDL_Window*, a pointer to an SDL_Window structure that represents the game window.
 *   Renderer: An alias for SDL_Renderer*, a pointer to an SDL_Renderer structure used for 2D rendering.
 *   Event: An alias for SDL_Event, which represents an event (like keyboard or mouse input) in SDL.
 *   Controller: An alias for SDL_GameController*, a pointer to an SDL_GameController structure representing a game controller.
 */
typedef SDL_Rect Rect;
typedef SDL_Window* Window;
typedef SDL_Renderer* Renderer;
typedef SDL_Event Event;
typedef SDL_GameController* Controller;
typedef SDL_Texture NGPL_Texture;
typedef SDL_Surface NGPL_Surface;

/*
 * NGPL-SDL Subsystem Variables
 * -----------------------
 * These variables represent different SDL subsystems used in initializing SDL functionality.
 * They are used with SDL_Init and related functions to start specific SDL features needed for the game.
 *
 * Variables:
 *   Video_SubSystem: Represents the SDL video subsystem (SDL_INIT_VIDEO).
 *   Audio_SubSystem: Represents the SDL audio subsystem (SDL_INIT_AUDIO).
 *   Timer_SubSystem: Represents the SDL timer subsystem (SDL_INIT_TIMER).
 *   Events_SubSystem: Represents the SDL events subsystem (SDL_INIT_EVENTS).
 *   All_SubSystem: Represents all SDL subsystems (SDL_INIT_EVERYTHING).
 *   Joystick_SubSystem: Represents the SDL joystick subsystem (SDL_INIT_JOYSTICK).
 *   Controller_SubSystem: Represents the SDL game controller subsystem (SDL_INIT_GAMECONTROLLER).
 */
Uint32 Video_SubSystem;
Uint32 Audio_SubSystem;
Uint32 Timer_SubSystem;
Uint32 Events_SubSystem;
Uint32 All_SubSystem;
Uint32 Joystick_SubSystem;
Uint32 Controller_SubSystem;

// Structs
/*
 * Struct: Vector2D
 * ----------------
 * Represents a 2D vector with floating-point coordinates.
 *
 * This structure is used for representing 2D points or vectors in space, with 'x' and 'y'
 * as its coordinates. Commonly used in various calculations for positioning, movement,
 * and physics in 2D space.
 *
 * Members:
 *   x: The x-coordinate of the vector.
 *   y: The y-coordinate of the vector.
 */
typedef struct Vector2D {
    float x;
    float y;
}Vector2D;

typedef struct Clock
{
    float FPS;
    int maxFPS;
    float TPF;
    Uint32 lastTime;
    float deltaTime;
    float frameCount;
    Uint32 currentTime;
} Clock;

// Functions
/*
 * Function: NGPL_Test
 * ----------------------------
 * Returns a test message if NGPL is initialize correctly.
 *
 * Returns: 
 *   A character array.
 */
char* NGPL_Test();

/*
 * Function: NGPL_Init
 * ---------------------------
 * Attempts to initialize the core components of NGPL (SDL2,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *    Void.
 */
void NGPL_Init();

/*
 * Function: NGPL_InitSubSystem
 * ---------------------------
 * Attempts to initialize the SubSystem passed in.
 * Prints a success message if components initialize properly
 * Prints an error message if components fail to initialize properly
 * 
 * Returns: 
 *   Void.
 */
int NGPL_InitSubSystem(Uint32 flags);

/*
 * Function: NGPL_GetKey
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
int NGPL_GetKey(Event event);

/*
 * Function: NGPL_GetEvent
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
bool NGPL_GetEvent(Event* event, Window window, Renderer renderer);

/*
 * Function: NGPL_CleanUp
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
void NGPL_CleanUp(Renderer renderer, Window window);

/*
 * Function: NGPL_GetKeyState
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
const Uint8* NGPL_GetKeyState(int* numKeys);

#endif