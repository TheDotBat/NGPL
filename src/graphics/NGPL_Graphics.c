#include "../../include/NGPL_Graphics.h"


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
Window NGPL_CreateWindow(int width, int height, const char* title)
{
    Window window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);

    if (!window)
    {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

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

Renderer NGPL_CreateRenderer(Window window, int driverIndex, Uint32 flags)
{
    Renderer r = SDL_CreateRenderer(window, driverIndex, flags);
    if (r == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "\nFailed to create renderer!\n%s", SDL_GetError());
    }
    return r;
}

void NGPL_ClearScreen(Renderer renderer, int color[4])
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderClear(renderer);
}

void NGPL_SendFrame(Renderer renderer)
{
    SDL_RenderPresent(renderer);
}

void NGPL_BlitRect(Renderer renderer, int color[4], Rect* rect)
{
    SDL_SetRenderDrawColor(renderer, color[0],color[1],color[2],color[3]);
    SDL_RenderFillRect(renderer, rect);
}
