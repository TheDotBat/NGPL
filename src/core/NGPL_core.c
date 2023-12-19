#include "../../include/NGPL_Core.h"

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
 * Function: NGPL_Test
 * ----------------------------
 * Returns a test message if NGPL is initialize correctly.
 *
 * Returns: 
 *   A character array.
 */
char* NGPL_Test()
{
    return "\nNGPL Test\n";
}

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
void NGPL_Init()
{
    if (SDL_Init(Video_SubSystem) != 0)
    {
        fprintf(stderr, "\nFailed to initialize core NGPL components...\n%s\n",SDL_GetError());
    } else {
        printf("\nNGPL Initialized!\n");
    }
}

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
int NGPL_InitSubSystem(Uint32 flags)
{
    if (SDL_InitSubSystem(flags) != 0)
    {
        fprintf(stderr, "\nFailed to initialize SubSystem...\n%s\n",SDL_GetError());
        return 1;
    } else {
        printf("\nSubSystem Initialized!\n");
        return 0;
    }
}

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
int NGPL_GetKey(Event event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        return event.key.keysym.scancode;
    }
    return SDL_SCANCODE_UNKNOWN;
}

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
bool NGPL_GetEvent(Event* event, Window window, Renderer renderer) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                // Handle Quit event (e.g., window close)
                SDL_DestroyWindow(window);
	            SDL_DestroyRenderer(renderer);
	            SDL_Quit();
                break;
            default:
                break;
        }
        return true;
    }
    return false;
}

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
void NGPL_CleanUp(Renderer renderer, Window window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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
const Uint8* NGPL_GetKeyState(int* numKeys)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(numKeys);
    return keyboardState;
}

