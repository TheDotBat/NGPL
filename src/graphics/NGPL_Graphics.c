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

void NGPL_BlitCircleF(Renderer renderer, int x, int y, int radius)
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

void NGPL_DrawEdge(Renderer ren, Edge* edge, NGPL_Color color)
{
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(ren, edge->V1.x, edge->V1.y, edge->V2.x, edge->V2.y);
}

NGPL_Rect NGPL_CreateRect(int w, int h, float x, float y)
{
    NGPL_Rect r;
    
    r.x = x;
    r.y = y;

    r.w = w;
    r.h = h;

    Edge left = {{r.x, r.y}, {r.x, r.y+r.h}};
    Edge top = {{r.x, r.y}, {r.x+r.w, r.y}};
    Edge right = {{r.x+r.w, r.y}, {r.x+r.w, r.y+r.h}};
    Edge bottom = {{r.x, r.y+r.h}, {r.x+r.w, r.y+r.h}};
    
    r.left = left;
    r.top = top;
    r.right = right;
    r.bottom = bottom;

    return r;
}

void NGPL_UpdateRect(NGPL_Rect* r)
{
    Edge left = {{r->x, r->y}, {r->x, r->y+r->h}};
    r->left = left;
    Edge top = {{r->x, r->y}, {r->x+r->w, r->y}};
    r->top = top;
    Edge right = {{r->x+r->w, r->y}, {r->x+r->w, r->y+r->h}};
    r->right = right;
    Edge bottom = {{r->x, r->y+r->h}, {r->x+r->w, r->y+r->h}};
    r->bottom = bottom;
}

void NGPL_BlitRect(Renderer ren, NGPL_Rect* r, NGPL_Color color)
{
    NGPL_DrawEdge(ren, &r->left, color);
    NGPL_DrawEdge(ren, &r->top, color);
    NGPL_DrawEdge(ren, &r->right, color);
    NGPL_DrawEdge(ren, &r->bottom, color);
}

void NGPL_RenderEntitySpriteRect(Renderer ren, NGPL_Entity* e)
{
    if (e->rb == NULL)
    {
        SDL_RenderFillRect(ren, &e->sprite.imgRect);
    } else {
        SDL_RenderFillRect(ren, &e->sprite.imgRect);    // imgRect needs to be updated to match rb->r when present
        NGPL_BlitRect(ren, &e->rb->r, e->sprite.color);
    }
}

void NGPL_BlitPSpace(NGPL_PSpace* space, Renderer ren)
{
    for (int i = 0; i < space->rows; i++)
    {
        for (int j = 0; j < space->cols; j++)
        {
            for ( int rbs = 0; rbs < space->cells[i][j].entityCount; rbs++)
            {
                NGPL_BlitRigidBody(ren, space->cells[i][j].entities[rbs], (NGPL_Color){255,0,0,255});
            }
        }
    }

}

void NGPL_RenderPoolE(Renderer ren, NGPL_PoolE* pool, NGPL_Camera* cam)
{
    for (int entity = 0; entity < pool->size; entity++)
    {
        Rect renderRect;
        renderRect.x = (int)pool->entities[entity]->sprite.imgRect.x - cam->position.x;
        renderRect.y = (int)pool->entities[entity]->sprite.imgRect.y - cam->position.y;
        renderRect.w = (int)pool->entities[entity]->sprite.imgRect.w;
        renderRect.h = (int)pool->entities[entity]->sprite.imgRect.h;
        SDL_RenderCopy(ren, pool->entities[entity]->sprite.image, NULL, &renderRect);
    }
}

void NGPL_RenderSpace(Renderer ren, NGPL_PSpace* space, NGPL_Camera* cam, NGPL_PoolR* poolR)
{
    if (poolR->clearScreen)
    {
        int color[4] = {poolR->clearColor.r, poolR->clearColor.g, poolR->clearColor.b, poolR->clearColor.a};
        NGPL_ClearScreen(ren, color);
    }
    if (poolR->showSpaceGrid)
    {
        NGPL_PSpaceShowGrid(ren, space, poolR->gridColor);
    }
    if (poolR->entityPool != NULL)
    {
        NGPL_RenderPoolE(ren, poolR->entityPool, cam);
    }
    if (poolR->showSpaceBodies)
    {
        NGPL_BlitPSpace(space, ren);
    }
}

void NGPL_ToggleBorderless(Window window)
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
