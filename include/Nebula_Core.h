#ifndef NEBULA_CORE_H
#define NEBULA_CORE_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#undef main


// CONSTANTS
typedef SDL_Window* Window;
typedef SDL_Renderer* Renderer;
Uint32 Video_SubSystem;
Uint32 Audio_SubSystem;
Uint32 Timer_SubSystem;
Uint32 Events_SubSystem;
Uint32 All_SubSystem;
Uint32 Joystick_SubSystem;
Uint32 Controller_SubSystem;

// Functions
char* Nebula_Test();
void Nebula_Init();
void Nebula_InitSubSystem(Uint32 flags);

#endif