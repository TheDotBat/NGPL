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

#ifndef NGPLG_H
#define NGPLG_H
#include "NGPL.h"


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
void NGPL_SetKeyBinds(SDL_Scancode moveUp, SDL_Scancode moveDown, SDL_Scancode moveLeft, SDL_Scancode moveRight, SDL_Scancode jump, SDL_Scancode attack, SDL_Scancode menu);

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
void NGPL_CreateSprite(NGPL_Entity* e, Vector2 size, NGPL_Color color);

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
NGPL_Entity NGPL_CreateEntity(PSpace* space, Vector2F position, Vector2 size, NGPL_Color color);

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
NGPL_Texture* NGPL_CreateTexture(Renderer renderer, const char* fp);

void NGPL_SetEntityTag(const char* tag, NGPL_Entity* e);

void NGPL_SetEntityImageOffsetX(NGPL_Entity* e, int offsetX);

void NGPL_SetEntityImageOffsetY(NGPL_Entity* e, int offsetY);

void NGPL_LoadSetEntityImage(Renderer ren, NGPL_Entity* e, const char* fp);

#include "NGPLG_Physics.h"
#endif