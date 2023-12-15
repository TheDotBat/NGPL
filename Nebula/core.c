#include "core.h"

// CONSTANTS

Uint32 Video_SubSystem = SDL_INIT_VIDEO;
Uint32 Audio_SubSystem = SDL_INIT_AUDIO;
Uint32 Timer_SubSystem = SDL_INIT_TIMER;
Uint32 Events_SubSystem = SDL_INIT_EVENTS;
Uint32 All_SubSystem = SDL_INIT_EVERYTHING;
Uint32 Joystick_SubSystem = SDL_INIT_JOYSTICK;
Uint32 Controller_SubSystem = SDL_INIT_GAMECONTROLLER;

// Core Functions

/*
 * Function: Nebula_Test
 * ----------------------------
 * Returns a test message if Nebula is initialize correctly.
 *
 * returns: A test message.
 */
char* Nebula_Test()
{
    return "\nNebula Test\n";
}

/*
 * Function: Nebula_Init
 * ---------------------------
 * Attempts to initialize the core components of Nebula (SDL2,...)
 * Prints a success message if all components initialize properly
 * Prints an error message if components fail to initialize properly
 * returns: Void
 */
void Nebula_Init()
{
    if (SDL_Init(Video_SubSystem) != 0)
    {
        fprintf(stderr, "\nFailed to initialize core Nebula components...\n%s\n",SDL_GetError());
    } else {
        printf("\nNebula Initialized!\n");
    }
}

/*
 * Function: Nebula_InitSubSystem
 * ---------------------------
 * Attempts to initialize the SubSystem passed in.
 * Prints a success message if components initialize properly
 * Prints an error message if components fail to initialize properly
 * returns: Void
 */
void Nebula_InitSubSystem(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0)
    {
        fprintf(stderr, "\nFailed to initialize SubSystem...\n%s\n",SDL_GetError());
    } else {
        printf("\nSubSystem Initialized!\n");
    }
}

/*
 * Function: Nebula_CreateRenderer
 * ---------------------------------
 * Attempts to create a renderer using SDL2.
 * Will return NULL and print an error message on fail.
 *
 * window: A pointer to an SDL2 window created with Nebula_CreateWindow()
 * driverIndex: An integer value indicating the rendering driver you wish to initialize. ( Use -1 to init the first one that supports your flags )
 * flags: Can be 0 or one or more valid SDL_RendererFlags OR'd together. ( Uses SDL_RENDERER_ACCELERATED by default ( Hardware acceleration ) )
 *
 * returns: A pointer to an SDL2 Renderer struct created with the passed parameters.
*/

Renderer Nebula_CreateRenderer(Window window, int driverIndex, Uint32 flags)
{
    Renderer r = SDL_CreateRenderer(window, driverIndex, flags);
    if (r == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "\nFailed to create renderer!\n%s", SDL_GetError());
    }
    return r;
}

NRect Nebula_CreateRect(float x, float y, int w, int h, int r, int g, int b, int a)
{
    NRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    rect.color[0] = r;
    rect.color[1] = g;
    rect.color[2] = b;
    rect.color[3] = a;
    return rect;
}

void Nebula_Blit(Renderer renderer)
{
    
}

void Nebula_ClearScreen(Renderer renderer, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

/*
 * Function: Nebula_CreateWindow
 * -----------------------------------------
 * Creates a new window using SDL2.
 *
 * width: Width of the window
 * height: Height of the window
 * title: Title of the window
 *
 * returns: Pointer to the created Window, or NULL on failure
 */
Window Nebula_CreateWindow(int width, int height, const char* title)
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

