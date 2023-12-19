#ifndef NGPL_GRAPHICS_H
#define NGPL_GRAPHICS_H
#include "NGPL.h"


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

/*
 * Function: NGPL_BlitRect
 * -----------------------------------------
 * Fills a rectangular area on the screen with the specified color.
 *
 * This function sets the render draw color for the provided renderer and then
 * fills a specified rectangular area with that color. It can be used for rendering
 * simple colored shapes like backgrounds, UI elements, or debug visuals.
 *
 * Parameters:
 *   renderer: The SDL_Renderer object used for rendering.
 *   color: An array of 4 integers representing the RGBA values of the fill color.
 *   rect: A pointer to an SDL_Rect struct defining the position and size of the rectangle.
 *
 * Returns:
 *   void: This function does not return a value.
 */
void NGPL_BlitRect(Renderer renderer, int color[4], Rect* rect);


#endif