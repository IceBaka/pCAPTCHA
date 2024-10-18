#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Chipmunk-7.0.3/include/chipmunk/chipmunk.h"
#include "gui.h"

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



    // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
    cpVect gravity = cpv(0, -500);
    
    // Create an empty space.
    cpSpace *space = cpSpaceNew();
    cpSpaceSetGravity(space, gravity);
    
    // Add a static line segment shape for the ground.
    // We'll make it slightly tilted so the ball will roll off.
    // We attach it to a static body to tell Chipmunk it shouldn't be movable.
    cpShape *ground = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(0, -APP_WINDOW_H*0.75), cpv(APP_WINDOW_W, -APP_WINDOW_H*0.75), 0);
    cpShapeSetFriction(ground, 1);
    cpSpaceAddShape(space, ground);
    
    // Now let's make a ball that falls onto the line and rolls off.
    // First we need to make a cpBody to hold the physical properties of the object.
    // These include the mass, position, velocity, angle, etc. of the object.
    // Then we attach collision shapes to the cpBody to give it a size and shape.
    
    cpFloat radius = 5;
    cpFloat mass = 1;
    
    // The moment of inertia is like mass for rotation
    // Use the cpMomentFor*() functions to help you approximate it.
    cpFloat moment = cpMomentForBox(mass, 50, 50);
    
    // The cpSpaceAdd*() functions return the thing that you are adding.
    // It's convenient to create and add an object in one line.
    cpBody *boxBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(boxBody, cpv(100, 0));
    
    // Now we create the collision shape for the ball.
    // You can create multiple collision shapes that point to the same body.
    // They will all be attached to the body and move around to follow it.
    cpShape *boxShape = cpSpaceAddShape(space, cpBoxShapeNew(boxBody,50,50,0));
    cpShapeSetFriction(boxShape, 0.7);


    SDL_Rect block_r = {100,0,50,50};
    Node *p = addControl(&ControlList,"block",block_r,BlockHandler,test0,NULL,NULL);
    CONTROL_NODE_DATA *block_controldata = p->node_data;
    block_controldata->data=malloc(sizeof(cpBody*));
    *((cpBody**)(block_controldata->data)) = boxBody;

    
    cpBody *boxBody2 = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(boxBody2, cpv(200, 0));
    cpShape *boxShape2 = cpSpaceAddShape(space, cpBoxShapeNew(boxBody2,50,50,0));
    cpShapeSetFriction(boxShape2, 0.7);
    
    SDL_Rect block_r2 = {200,0,50,50};
    Node *p2 = addControl(&ControlList,"block",block_r2,BlockHandler,test0,NULL,NULL);
    CONTROL_NODE_DATA *block_controldata2 = p2->node_data;
    block_controldata2->data=malloc(sizeof(cpBody*));
    *((cpBody**)(block_controldata2->data)) = boxBody2;

    cpSpaceAddConstraint(space,cpPivotJointNew(boxBody,boxBody2,cpv(150,0)));
    
    
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

        cpVect boxPos= cpBodyGetPosition(boxBody);
        block_controldata->area.x = boxPos.x;block_controldata->area.y = -boxPos.y;
        cpVect boxPos2= cpBodyGetPosition(boxBody2);
        block_controldata2->area.x = boxPos2.x;block_controldata2->area.y = -boxPos2.y;

        drawControls(ControlList);
        CheckMouse(ControlList);
        RunJobs(JobList);
        
        SDL_RenderPresent(APP_Renderer);

    }
    
    IMG_Quit();
    SDL_DestroyRenderer(APP_Renderer);
    SDL_DestroyWindow(APP_Window);
    SDL_Quit();
}