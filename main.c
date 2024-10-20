#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Chipmunk-7.0.3/include/chipmunk/chipmunk.h"
#include "gui.h"
#include "captcha.h"

int main(int argc,char *argv[])
{
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS,"permonitor");
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
    
    APP_Window = SDL_CreateWindow("CAPTCHA DEMO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,APP_WINDOW_W,APP_WINDOW_H,SDL_WINDOW_SHOWN|SDL_WINDOW_BORDERLESS);
    APP_Renderer = SDL_CreateRenderer(APP_Window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture *test0 = IMG_LoadTexture(APP_Renderer,"test0.png");
    SDL_Texture *test1 = IMG_LoadTexture(APP_Renderer,"test1.png");
    // SDL_Rect hi_r = {0,0,APP_WINDOW_W*0.5,APP_WINDOW_H};
    // addControl(&ControlList,"sayhi",hi_r,ButtonSayhiHandler,test0,test0,test1);
    // SDL_Rect drag_r = {APP_WINDOW_W*0.5,0,APP_WINDOW_W*0.5,APP_WINDOW_H};
    // addControl(&ControlList,"drag",drag_r,topbarHandler,NULL,NULL,NULL);

    
    Uint32 startTime = SDL_GetTicks();
    Uint32 lastTime = SDL_GetTicks();

    int QUIT = 0;
    SDL_Event e;
    while (!QUIT)
    {
        while (SDL_PollEvent(&e))
        {   
            if(e.type == SDL_WINDOWEVENT)
            {
                if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    QUIT=1;
                }
            }
        }

        SDL_SetRenderDrawColor(APP_Renderer,125,125,125,255);
        SDL_RenderClear(APP_Renderer);

        lastTime = SDL_GetTicks();
        cpSpaceStep(space, (lastTime - startTime) / 1000.0);
        startTime = SDL_GetTicks();

        UpdateCaptchaControls(CaptchaControlList);

        drawControls(ControlList);
        drawControls(CaptchaControlList);
        CheckMouse(ControlList);
        RunJobs(JobList);
        
        SDL_RenderPresent(APP_Renderer);

    }
    
    IMG_Quit();
    SDL_DestroyRenderer(APP_Renderer);
    SDL_DestroyWindow(APP_Window);
    SDL_Quit();
}