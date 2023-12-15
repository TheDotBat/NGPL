#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdbool.h>
#include "common.h"

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

// DECLARATIONS
char* Nebula_Test();
void Nebula_Init();
void Nebula_InitSubSystem(Uint32 flags);
void Nebula_ClearScreen(Renderer renderer, int r, int g, int b, int a);
void Nebula_Blit(Renderer renderer);
Renderer Nebula_CreateRenderer(Window window, int driverIndex, Uint32 flags);
SDL_Window* Nebula_CreateWindow(int width, int height, const char* title);

#endif
