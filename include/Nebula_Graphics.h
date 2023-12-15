#ifndef NEBULA_GRAPHICS_H
#define NEBULA_GRAPHICS_H

#include "Nebula.h"

void Nebula_Blit(Renderer renderer);
void Nebula_ClearScreen(Renderer renderer, int r, int g, int b, int a);
SDL_Window* Nebula_CreateWindow(int width, int height, const char* title);
Renderer Nebula_CreateRenderer(Window window, int driverIndex, Uint32 flags);

#endif