#include "../../include/NDL_G.h"


/*
 * Function: NDL_CreateWindow
 * -----------------------------------------
 * Creates a new window using SDL2.
 *
 * width: Width of the window
 * height: Height of the window
 * title: Title of the window
 *
 * returns: Pointer to the created Window, or NULL on failure
 */
Window NDL_CreateWindow(int width, int height, const char* title)
{
    Window window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

/*
 * Function: NDL_CreateRenderer
 * ---------------------------------
 * Attempts to create a renderer using SDL2.
 * Will return NULL and print an error message on fail.
 *
 * window: A pointer to an SDL2 window created with NDL_CreateWindow()
 * driverIndex: An integer value indicating the rendering driver you wish to initialize. ( Use -1 to init the first one that supports your flags )
 * flags: Can be 0 or one or more valid SDL_RendererFlags OR'd together. ( Uses SDL_RENDERER_ACCELERATED by default ( Hardware acceleration ) )
 *
 * returns: A pointer to an SDL2 Renderer struct created with the passed parameters.
*/
Renderer NDL_CreateRenderer(Window window, int driverIndex, Uint32 flags)
{
    Renderer r = SDL_CreateRenderer(window, driverIndex, flags);
    if (r == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "\nFailed to create renderer!\n%s", SDL_GetError());
    }
    return r;
}

void NDL_ClearScreen(Renderer renderer, int color[4])
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderClear(renderer);
}

void NDL_SendFrame(Renderer renderer)
{
    SDL_RenderPresent(renderer);
}

void NDL_BlitCircleF(Renderer renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void NDL_DrawEdge(Renderer ren, NDL_Edge* edge, NDL_Color color)
{
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(ren, edge->V1.x, edge->V1.y, edge->V2.x, edge->V2.y);
}

NDL_Rect NDL_CreateRect(int w, int h, float x, float y)
{
    NDL_Rect r;
    
    r.x = x;
    r.y = y;

    r.w = w;
    r.h = h;

    NDL_Edge left = {{r.x, r.y}, {r.x, r.y+r.h}};
    NDL_Edge top = {{r.x, r.y}, {r.x+r.w, r.y}};
    NDL_Edge right = {{r.x+r.w, r.y}, {r.x+r.w, r.y+r.h}};
    NDL_Edge bottom = {{r.x, r.y+r.h}, {r.x+r.w, r.y+r.h}};
    
    r.left = left;
    r.top = top;
    r.right = right;
    r.bottom = bottom;

    return r;
}

void NDL_UpdateRect(NDL_Rect* r)
{
    NDL_Edge left = {{r->x, r->y}, {r->x, r->y+r->h}};
    r->left = left;
    NDL_Edge top = {{r->x, r->y}, {r->x+r->w, r->y}};
    r->top = top;
    NDL_Edge right = {{r->x+r->w, r->y}, {r->x+r->w, r->y+r->h}};
    r->right = right;
    NDL_Edge bottom = {{r->x, r->y+r->h}, {r->x+r->w, r->y+r->h}};
    r->bottom = bottom;
}

void NDL_BlitRect(Renderer ren, NDL_Rect* r, NDL_Color color)
{
    NDL_DrawEdge(ren, &r->left, color);
    NDL_DrawEdge(ren, &r->top, color);
    NDL_DrawEdge(ren, &r->right, color);
    NDL_DrawEdge(ren, &r->bottom, color);
}

void NDL_ToggleBorderless(Window window)
{
    Uint32 flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
        SDL_SetWindowFullscreen(window, 0); // Turn off borderless fullscreen
        SDL_SetWindowBordered(window, SDL_TRUE); // Add window border
    } else {
        SDL_SetWindowBordered(window, SDL_FALSE); // Remove window border
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // Turn on borderless fullscreen
    }
}

void FillRect(Renderer ren, Rect* rect, NDL_Color color)
{
    SDL_SetRenderDrawColor(ren, color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(ren, rect);
}

void NDL_BlitTexture(Renderer ren, NDL_Texture* image, Rect* rect)
{
    SDL_RenderCopy(ren, image, NULL, rect);
}

void BlitColliderComponent(Renderer ren, ColliderComponent* collider, NDL_Color color)
{
    NDL_BlitRect(ren, &collider->r, color);
}

void Render(RenderSystem* renSys)
{
    Pool* pool = renSys->pool;
    Renderer ren = renSys->sdlRenderer;
    int clearColor[4] = {renSys->clearColor.r, renSys->clearColor.g, renSys->clearColor.b, renSys->clearColor.a};
    NDL_ClearScreen(renSys->sdlRenderer, clearColor);
    for (int i = 0; i < pool->size; i++)
    {
        if (HasComponent(pool->entities[i], SPRITE_COMPONENT))
        {
            Rect renderRect;
            renderRect.x = (int)pool->entities[i]->sprite->imageRect.x;// - cam->position.x;
            renderRect.y = (int)pool->entities[i]->sprite->imageRect.y;// - cam->position.y;
            renderRect.w = (int)pool->entities[i]->sprite->imageRect.w;
            renderRect.h = (int)pool->entities[i]->sprite->imageRect.h;
            pool->entities[i]->sprite->image == NULL ? FillRect(ren, &pool->entities[i]->sprite->imageRect, pool->entities[i]->sprite->color) : NDL_BlitTexture(ren, pool->entities[i]->sprite->image, &renderRect);

            if (HasComponent(pool->entities[i], COLLIDER_COMPONENT) & renSys->showColliders)
            {
                BlitColliderComponent(ren, pool->entities[i]->collider, pool->entities[i]->sprite->color);
            }
        }
    }
}

RenderSystem* CreateRenderSystem(Renderer sdlRenderer, NDL_Color clearColor)
{
    RenderSystem* renSys = malloc(sizeof(RenderSystem));
    renSys->pool = NULL;
    renSys->showColliders = false;
    renSys->clearColor = clearColor;
    renSys->sdlRenderer = sdlRenderer;
    renSys->render = Render;
    return renSys;
}

void SetRenderSystemPool(RenderSystem* renSys, Pool* pool)
{
    renSys->pool = pool;
}


