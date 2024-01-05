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

#ifndef NDL_C_H
#define NDL_C_H

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

#define NDL_KEY_UP_ARROW SDL_SCANCODE_UP
#define NDL_KEY_DOWN_ARROW SDL_SCANCODE_DOWN
#define NDL_KEY_LEFT_ARROW SDL_SCANCODE_LEFT
#define NDL_KEY_RIGHT_ARROW SDL_SCANCODE_RIGHT

#define NDL_KEY_A SDL_SCANCODE_A
#define NDL_KEY_B SDL_SCANCODE_B
#define NDL_KEY_C SDL_SCANCODE_C
#define NDL_KEY_D SDL_SCANCODE_D
#define NDL_KEY_E SDL_SCANCODE_E
#define NDL_KEY_F SDL_SCANCODE_F
#define NDL_KEY_G SDL_SCANCODE_G
#define NDL_KEY_H SDL_SCANCODE_H
#define NDL_KEY_I SDL_SCANCODE_I
#define NDL_KEY_J SDL_SCANCODE_J
#define NDL_KEY_K SDL_SCANCODE_K
#define NDL_KEY_L SDL_SCANCODE_L
#define NDL_KEY_M SDL_SCANCODE_M
#define NDL_KEY_N SDL_SCANCODE_N
#define NDL_KEY_O SDL_SCANCODE_O
#define NDL_KEY_P SDL_SCANCODE_P
#define NDL_KEY_Q SDL_SCANCODE_Q
#define NDL_KEY_R SDL_SCANCODE_R
#define NDL_KEY_S SDL_SCANCODE_S
#define NDL_KEY_T SDL_SCANCODE_T
#define NDL_KEY_U SDL_SCANCODE_U
#define NDL_KEY_V SDL_SCANCODE_V
#define NDL_KEY_W SDL_SCANCODE_W
#define NDL_KEY_X SDL_SCANCODE_X
#define NDL_KEY_Y SDL_SCANCODE_Y
#define NDL_KEY_Z SDL_SCANCODE_Z

#define NDL_KEY_0 SDL_SCANCODE_0
#define NDL_KEY_1 SDL_SCANCODE_1
#define NDL_KEY_2 SDL_SCANCODE_2
#define NDL_KEY_3 SDL_SCANCODE_3
#define NDL_KEY_4 SDL_SCANCODE_4
#define NDL_KEY_5 SDL_SCANCODE_5
#define NDL_KEY_6 SDL_SCANCODE_6
#define NDL_KEY_7 SDL_SCANCODE_7
#define NDL_KEY_8 SDL_SCANCODE_8
#define NDL_KEY_9 SDL_SCANCODE_9

#define NDL_KEY_SPACE SDL_SCANCODE_SPACE
#define NDL_KEY_ENTER SDL_SCANCODE_RETURN
#define NDL_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define NDL_KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define NDL_KEY_TAB SDL_SCANCODE_TAB
#define NDL_KEY_SHIFT SDL_SCANCODE_LSHIFT
#define NDL_KEY_CTRL SDL_SCANCODE_LCTRL
#define NDL_KEY_ALT SDL_SCANCODE_LALT
#define NDL_KEY_RSHIFT SDL_SCANCODE_RSHIFT
#define NDL_KEY_RCTRL SDL_SCANCODE_RCTRL
#define NDL_KEY_RALT SDL_SCANCODE_RALT

#define NDL_KEYUP SDL_KEYUP
#define NDL_KEYDOWN SDL_KEYDOWN

#define NDL_CONTROLLER_BUTTON_A SDL_CONTROLLER_BUTTON_A
#define NDL_CONTROLLER_BUTTON_B SDL_CONTROLLER_BUTTON_B
#define NDL_CONTROLLER_BUTTON_X SDL_CONTROLLER_BUTTON_X
#define NDL_CONTROLLER_BUTTON_Y SDL_CONTROLLER_BUTTON_Y
#define NDL_CONTROLLER_BUTTON_BACK SDL_CONTROLLER_BUTTON_BACK
#define NDL_CONTROLLER_BUTTON_GUIDE SDL_CONTROLLER_BUTTON_GUIDE
#define NDL_CONTROLLER_BUTTON_START SDL_CONTROLLER_BUTTON_START
#define NDL_CONTROLLER_BUTTON_LEFTSTICK SDL_CONTROLLER_BUTTON_LEFTSTICK
#define NDL_CONTROLLER_BUTTON_RIGHTSTICK SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define NDL_CONTROLLER_BUTTON_LEFTSHOULDER SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define NDL_CONTROLLER_BUTTON_RIGHTSHOULDER SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define NDL_CONTROLLER_BUTTON_DPAD_UP SDL_CONTROLLER_BUTTON_DPAD_UP
#define NDL_CONTROLLER_BUTTON_DPAD_DOWN SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define NDL_CONTROLLER_BUTTON_DPAD_LEFT SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define NDL_CONTROLLER_BUTTON_DPAD_RIGHT SDL_CONTROLLER_BUTTON_DPAD_RIGHT

#define NDL_CONTROLLER_AXIS_LEFTX SDL_CONTROLLER_AXIS_LEFTX
#define NDL_CONTROLLER_AXIS_LEFTY SDL_CONTROLLER_AXIS_LEFTY
#define NDL_CONTROLLER_AXIS_RIGHTX SDL_CONTROLLER_AXIS_RIGHTX
#define NDL_CONTROLLER_AXIS_RIGHTY SDL_CONTROLLER_AXIS_RIGHTY
#define NDL_CONTROLLER_AXIS_TRIGGERLEFT SDL_CONTROLLER_AXIS_TRIGGERLEFT
#define NDL_CONTROLLER_AXIS_TRIGGERRIGHT SDL_CONTROLLER_AXIS_TRIGGERRIGHT

#define NDL_CONTROLLER_BUTTON_DOWN SDL_CONTROLLERBUTTONDOWN
#define NDL_CONTROLLER_BUTTON_UP SDL_CONTROLLERBUTTONUP
#define NDL_CONTROLLER_AXIS_MOTION SDL_CONTROLLERAXISMOTION


typedef SDL_Rect Rect;
typedef SDL_Window* Window;
typedef SDL_Renderer* Renderer;
typedef SDL_Event Event;
typedef SDL_GameController* Controller;
typedef SDL_Texture NDL_Texture;
typedef SDL_Surface NDL_Surface;
typedef SDL_Color NDL_Color;
typedef struct Vector2 Vector2;
typedef struct Vector2F Vector2F;
typedef struct CollisionData CollisionData;
typedef struct NDL_Edge NDL_Edge;
typedef struct NDL_Camera NDL_Camera;
typedef struct PhysicsSystem PhysicsSystem;
typedef struct RenderSystem RenderSystem;
typedef struct PhysicsGrid PhysicsGrid;
typedef struct Clock Clock;
typedef struct NDL_Entity NDL_Entity;
typedef struct Keybinds Keybinds;
typedef struct NDL_Rect NDL_Rect;
typedef enum Components Components;
typedef struct SpriteComponent SpriteComponent;
typedef enum COLLISION_TYPES COLLISION_TYPES;
typedef struct ColliderComponent ColliderComponent;
typedef struct Pool Pool;
typedef enum PlayerActions PlayerActions;
typedef struct Cell Cell;
typedef void (*ForceMethod) (NDL_Entity*, PhysicsSystem*);
typedef void (*PosMethod) (PhysicsSystem*, NDL_Entity*, float, int);
typedef bool (*ColMethod) (PhysicsGrid*);
typedef void (*RenderMethod) ();
Uint32 Video_SubSystem;
Uint32 Audio_SubSystem;
Uint32 Timer_SubSystem;
Uint32 Events_SubSystem;
Uint32 All_SubSystem;
Uint32 Joystick_SubSystem;
Uint32 Controller_SubSystem;

struct Vector2
{
    int x;
    int y;
};

struct Vector2F
{
    float x;
    float y;
};

struct NDL_Edge
{
 Vector2F V1;
 Vector2F V2;
};

struct NDL_Rect
{
    float x;
    float y;
    int w;
    int h;
    NDL_Edge left;
    NDL_Edge top;
    NDL_Edge right;
    NDL_Edge bottom;
};

enum Components
{
    NO_COMPONENT = 0,
    SPRITE_COMPONENT = 1<<0, //0001
    COLLIDER_COMPONENT = 1<<1 //0010
};

struct SpriteComponent
{
    Rect imageRect;
    NDL_Color color;
    NDL_Texture* image;
    Vector2 imageOffset;
};

enum COLLISION_TYPES
{
    L,
    R,
    U,
    D,
    None
};

struct ColliderComponent
{
    const char* tag;
    bool isDynamic;
    bool isStatic;
    float mass;
    Vector2F position;
    Vector2F velocity;
    NDL_Rect r;
};

struct NDL_Entity
{
    const char* tag;
    bool isDynamic;
    Vector2F position;
    Vector2F velocity;
    unsigned int componentFlags;
    SpriteComponent* sprite;
    ColliderComponent* collider;
};

struct Pool
{
    int size;
    int maxSize;
    NDL_Entity** entities;
};

struct NDL_Camera
{
    Vector2F position;
    float cameraSpeed;
    float scrollInterpolation;
};

struct RenderSystem
{
    bool showColliders;
    Renderer sdlRenderer;
    Pool* pool;
    NDL_Color clearColor;
    RenderMethod render;
};

struct Cell
{
    Pool* pool;
};

struct PhysicsGrid
{
    int w,h;
    int r,c;
    int cellSize;
    Cell** cells;
};

struct PhysicsSystem
{
    bool forTopDown;
    bool frictionX;
    bool frictionY;
    PhysicsGrid* gridSpace;
    float gravity;
    Vector2F friction;
    ForceMethod handleForces;
    PosMethod handlePositions;
    ColMethod handleCollisions;
};

struct CollisionData
{
    bool none;
    ColliderComponent* _for;
    ColliderComponent* _against;
    Vector2F _point;  // Collision point
    float _massFor;
    float _massAgainst;
    Vector2F _velocityFor;
    COLLISION_TYPES _typeX;
    COLLISION_TYPES _typeY;
};

struct Clock
{
    float FPS;
    int maxFPS;
    float TPF;
    Uint32 lastTime;
    float deltaTime;
    float frameCount;
    Uint32 currentTime;
};

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
enum PlayerActions
{
    PLAYER_ACTION_NONE = 0,
    PLAYER_ACTION_MOVE_LEFT = 1 << 0, // 0001
    PLAYER_ACTION_MOVE_RIGHT = 1 << 1, // 0010
    PLAYER_ACTION_JUMP = 1 << 2, // 0100
    PLAYER_ACTION_MENU = 1 << 3, // 1000
    PLAYER_ACTION_MOVE_UP = 1 << 4, // 0001 0000
    PLAYER_ACTION_MOVE_DOWN = 1 << 5, // 0010 0000
    PLAYER_ACTION_ATTACK = 1 << 6, // 0100 0000
} ;

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
struct Keybinds
{
   SDL_Scancode moveUp;
   SDL_Scancode moveDown;
   SDL_Scancode moveLeft;
   SDL_Scancode moveRight;
   SDL_Scancode jump;
   SDL_Scancode menu;
   SDL_Scancode attack; // New control
};
Keybinds keyBinds;

#endif