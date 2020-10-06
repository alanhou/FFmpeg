#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("SDL2 Window",
                    200,400,
                    640,
                    480,
                    SDL_WINDOW_SHOWN);
    
    if(!window){
        printf("Failed to create window!");
        goto __EXIT;
    }

    render = SDL_CreateRenderer(window, -1, 0);
    if(!render){
        SDL_Log("Failed to create render!");
        goto __DWINDOW;
    }
    
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

    SDL_RenderClear(render);

    SDL_RenderPresent(render);

    SDL_Delay(3000);


__DWINDOW:
    SDL_DestroyWindow(window);

__EXIT: 
    SDL_Quit();
    return 0;
}
