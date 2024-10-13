#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#define APP_WINDOW_W 640
#define APP_WINDOW_H 395 //640*0.618

int main(int argc,char *argv[])
{
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitor");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"best");

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init Failed,Error:%s\n",SDL_GetError());
        return -1;
    }
    
    if (!IMG_Init(IMG_INIT_PNG))
    {
        printf("IMG_Init Failed,Error:%s\n",IMG_GetError());
        return -2;
    }
    
    SDL_Window *theWindow = SDL_CreateWindow("CAPTCHA DEMO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,APP_WINDOW_W,APP_WINDOW_H,SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    SDL_Renderer *theRenderer = SDL_CreateRenderer(theWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    int QUIT = 0;
    SDL_Event e;
    while (!QUIT)
    {
        while (SDL_PollEvent(&e))
        {   
            if(e.type==SDL_WINDOWEVENT)
            {
                if (e.window.event==SDL_WINDOWEVENT_CLOSE)
                {
                    QUIT=1;
                }
            }
        }

        SDL_SetRenderDrawColor(theRenderer,125,125,125,255);
        SDL_RenderClear(theRenderer);
        SDL_RenderPresent(theRenderer);

    }

}