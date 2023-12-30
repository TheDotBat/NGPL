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

#ifndef NGPL_CORE_H
#define NGPL_CORE_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//#include "SDL.h"
#include "cJSON.h"
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

typedef SDL_Color NGPL_Color;

// Structs
/*
 * Struct: Vector2F
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
typedef struct Vector2
{
    int x;
    int y;
}Vector2;

typedef struct Vector2F
{
    float x;
    float y;
}Vector2F;

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

typedef struct Edge
{
 Vector2F V1;
 Vector2F V2;
}Edge;

typedef struct NGPL_Rect
{
    float x;
    float y;
    int w;
    int h;
    Edge left;
    Edge top;
    Edge right;
    Edge bottom;
}NGPL_Rect;

typedef struct NGPL_Sprite
{
    NGPL_Texture* image;
    Rect imgRect;
    Vector2 size;
    NGPL_Color color;
    Vector2 imageOffset;
}NGPL_Sprite;

typedef struct NGPL_RigidBody
{
    const char* tag;
    bool isDynamic;
    bool isStatic;
    float mass;
    Vector2F position;
    Vector2F velocity;
    NGPL_Rect r;
    int cRow,cCol;
    bool topDown;
}NGPL_RigidBody;

typedef struct PGridCell
{
    NGPL_RigidBody** entities;
    int entityCount;
}PGridCell;

typedef enum COLLISION_TYPES
{
    L,
    R,
    U,
    D,
    None
}COLLISION_TYPES;

typedef struct CollisionInfo
{
    bool none;
    NGPL_RigidBody* dE;
    NGPL_RigidBody* sE;
    Vector2F point;  // Collision point
    float massDynamic;
    float massStatic;
    Vector2F velocityDynamic;
    COLLISION_TYPES typeX;
    COLLISION_TYPES typeY;
}CollisionInfo;

typedef struct NGPL_PSpace
{
    float g;
    float f;
    int cellSize;
    int rows;
    int cols;
    Rect bounds;
    PGridCell** cells;
}NGPL_PSpace;

/*
 * Struct: Entity
 * --------------
 * Represents a game object with position, size, velocity, and color.
 *
 * This structure defines a basic game object in 2D space, including its position,
 * size, velocity, and color. Used for representing and manipulating entities in the game.
 *
 * Members:
 *   position: A Vector2F representing the object's position in 2D space.
 *   size: A Vector2F representing the object's size.
 *   velocity: A Vector2F representing the object's velocity.
 *   color: An array of 4 integers representing the RGBA color of the object.
 */
typedef struct NGPL_Entity
{
    const char* tag;
    NGPL_RigidBody* rb;
    Vector2 size;
    Vector2F position;
    Vector2F velocity;
    NGPL_Sprite sprite;
}NGPL_Entity;

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
typedef enum PlayerActions {
    PLAYER_ACTION_NONE = 0,
    PLAYER_ACTION_MOVE_LEFT = 1 << 0, // 0001
    PLAYER_ACTION_MOVE_RIGHT = 1 << 1, // 0010
    PLAYER_ACTION_JUMP = 1 << 2, // 0100
    PLAYER_ACTION_MENU = 1 << 3, // 1000
    PLAYER_ACTION_MOVE_UP = 1 << 4, // 0001 0000
    PLAYER_ACTION_MOVE_DOWN = 1 << 5, // 0010 0000
    PLAYER_ACTION_ATTACK = 1 << 6, // 0100 0000
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
typedef struct Keybinds {
    SDL_Scancode moveUp;
    SDL_Scancode moveDown;
    SDL_Scancode moveLeft;
    SDL_Scancode moveRight;
    SDL_Scancode jump;
    SDL_Scancode menu;
    SDL_Scancode attack; // New control
} KeyBinds;
KeyBinds keyBinds;


typedef struct NGPL_PoolE
{
    NGPL_Entity** entities;
    int size;
    int maxSize;
}NGPL_PoolE;

typedef struct NGPL_Camera
{
    Vector2F position;
    float cameraSpeed;
    float scrollInterpolation;
}NGPL_Camera;

typedef struct NGPL_PoolR
{
    bool clearScreen;
    bool showSpaceGrid;
    bool showSpaceBodies;
    NGPL_Color gridColor;
    NGPL_Color clearColor;
    NGPL_PoolE* entityPool;
}NGPL_PoolR;

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