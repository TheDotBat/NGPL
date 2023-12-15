#include "../Nebula/core.h"
#include "../Nebula/common.h"

int main(int argv, char* argc[]) {
    printf(Nebula_Test());
    Nebula_Init();
    NRect myRect = { 100, 100, 32, 32, 0, 0, 255, 255 };
    Window window = Nebula_CreateWindow(800,500,"Nebula Window");
    Renderer renderer = Nebula_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Vector2 myVec = {200,120};
    
    // Game loop
    bool running = true;
    while(running != false)
    {
        Nebula_ClearScreen(renderer, 0, 255, 0, 255);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
