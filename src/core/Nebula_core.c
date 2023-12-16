#include "../../include/Nebula_Core.h"

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
