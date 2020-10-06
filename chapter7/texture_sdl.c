#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int quit = 1;
    SDL_Event event;

    SDL_Texture *texture = NULL;

    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;

    SDL_Rect rect;
    rect.w = 30;
    rect.h = 30;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("SDL2 Texture Demo",
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
   /* 
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

    SDL_RenderClear(render);

    SDL_RenderPresent(render);
    */

    texture = SDL_CreateTexture(render, 
                    SDL_PIXELFORMAT_RGBA8888, 
                    SDL_TEXTUREACCESS_TARGET,
                    640,
                    480);
    if(!texture){
        SDL_Log("Failed to create texture");
        goto __RENDER;
    }    

    do{
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            quit = 0;
            break;
        default:
            SDL_Log("event type is %d", event.type);
        }
        
        rect.x = rand() % 600;
        rect.y = rand() % 450;

        SDL_SetRenderTarget(render, texture);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
        SDL_RenderClear(render);

        SDL_RenderDrawRect(render, &rect);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
        SDL_RenderFillRect(render, &rect);

        SDL_SetRenderTarget(render, NULL);
        SDL_RenderCopy(render, texture, NULL, NULL);

        SDL_RenderPresent(render);

    }while(quit);
    
    SDL_DestroyTexture(texture);
    //SDL_Delay(3000);

__RENDER:    
    SDL_DestroyRenderer(render);

__DWINDOW:
    SDL_DestroyWindow(window);

__EXIT: 
    SDL_Quit();
    return 0;
}
