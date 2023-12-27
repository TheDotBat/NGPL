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

#ifndef NGPL_GRAPHICS_H
#define NGPL_GRAPHICS_H
#include "NGPL.h"


typedef SDL_Color NGPL_Color;

/*
 * Function: NGPL_CreateWindow
 * -----------------------------------------
 * Creates a new window using SDL2.
 *
 * width: Width of the window
 * height: Height of the window
 * title: Title of the window
 *
 * returns: Pointer to the created Window, or NULL on failure
 */
Window NGPL_CreateWindow(int width, int height, const char* title);

/*
 * Function: NGPL_CreateRenderer
 * ---------------------------------
 * Attempts to create a renderer using SDL2.
 * Will return NULL and print an error message on fail.
 *
 * window: A pointer to an SDL2 window created with NGPL_CreateWindow()
 * driverIndex: An integer value indicating the rendering driver you wish to initialize. ( Use -1 to init the first one that supports your flags )
 * flags: Can be 0 or one or more valid SDL_RendererFlags OR'd together. ( Uses SDL_RENDERER_ACCELERATED by default ( Hardware acceleration ) )
 *
 * returns: A pointer to an SDL2 Renderer struct created with the passed parameters.
*/
Renderer NGPL_CreateRenderer(Window window, int driverIndex, Uint32 flags);

/*
 * Function: NGPL_ClearScreen
 * -----------------------------------------
 * Clears the screen with the specified color.
 *
 * This function sets the render draw color of the provided renderer and then clears
 * the screen with that color. It is typically called at the beginning of a rendering
 * cycle to reset the screen before drawing new content.
 *
 * Parameters:
 *   renderer: The SDL_Renderer object used for rendering.
 *   color: An array of 4 integers representing the RGBA values of the color
 *          used to clear the screen.
 *
 * Returns:
 *   void: This function does not return a value.
 */
void NGPL_ClearScreen(Renderer renderer, int color[4]);

/*
 * Function: NGPL_SendFrame
 * -----------------------------------------
 * Presents the final rendering on the screen.
 *
 * This function updates the screen with any rendering performed since the previous call.
 * It is typically called at the end of a rendering cycle to display the final image
 * on the screen.
 *
 * Parameters:
 *   renderer: The SDL_Renderer object used for rendering.
 *
 * Returns:
 *   void: This function does not return a value.
 */
void NGPL_SendFrame(Renderer renderer);

void NGPL_BlitCircleF(Renderer renderer, int x, int y, int radius);

#endif