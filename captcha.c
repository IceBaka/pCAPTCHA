#include "gui.h"
#include "captcha.h"
#include "Chipmunk-7.0.3/include/chipmunk/chipmunk.h"

Node *CaptchaControlList;

cpSpace *space;
cpShape *wall_top;
cpShape *wall_bottom;
cpShape *wall_left;
cpShape *wall_right;
// cube

void genCAPTCHA()
{
    srand(time(NULL));

    cpVect gravity = cpv(0, -500);
    
    space = cpSpaceNew();
    cpSpaceSetGravity(space,gravity);
    
    wall_top = cpSegmentShapeNew(cpSpaceGetStaticBody(space),cpv(0,-APP_WINDOW_H*0.75),cpv(APP_WINDOW_W,-APP_WINDOW_H*0.75),0);
    wall_bottom = cpSegmentShapeNew(cpSpaceGetStaticBody(space),cpv(0,-APP_WINDOW_H*0.75),cpv(APP_WINDOW_W,-APP_WINDOW_H*0.75),0);
    wall_left = cpSegmentShapeNew(cpSpaceGetStaticBody(space),cpv(0,-APP_WINDOW_H*0.75),cpv(APP_WINDOW_W,-APP_WINDOW_H*0.75),0);
    wall_right = cpSegmentShapeNew(cpSpaceGetStaticBody(space),cpv(0,-APP_WINDOW_H*0.75),cpv(APP_WINDOW_W,-APP_WINDOW_H*0.75),0);
    cpShapeSetFriction(wall_top,1);
    cpShapeSetFriction(wall_bottom,1);
    cpShapeSetFriction(wall_left,1);
    cpShapeSetFriction(wall_right,1);
    cpSpaceAddShape(space,wall_top);
    cpSpaceAddShape(space,wall_bottom);
    cpSpaceAddShape(space,wall_left);
    cpSpaceAddShape(space,wall_right);
    
    // Now let's make a ball that falls onto the line and rolls off.
    // First we need to make a cpBody to hold the physical properties of the object.
    // These include the mass, position, velocity, angle, etc. of the object.
    // Then we attach collision shapes to the cpBody to give it a size and shape.
    
    cpFloat ball_radius = 5;
    cpFloat chain_w = 5;
    cpFloat chain_h = 5;
    cpFloat ball_mass = 100;
    cpFloat chain_mass = 1;
    
    // The moment of inertia is like mass for rotation
    // Use the cpMomentFor*() functions to help you approximate it.
    cpFloat ball_moment = cpMomentForCircle(ball_mass,0,ball_radius,cpvzero);
    cpFloat chain_moment = cpMomentForBox(chain_mass,chain_w,chain_h);
    
    // The cpSpaceAdd*() functions return the thing that you are adding.
    // It's convenient to create and add an object in one line.
    cpBody *ball_Body = cpSpaceAddBody(space,cpBodyNew(ball_mass,ball_moment));
    cpBodySetPosition(ball_Body, cpv(100, 0));
    
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


    addCaptchaControl();
    
}

void cleanCAPTCHA()
{
    cpfree;
}

// breakCube

void UpdateCaptchaControls(Node *CaptchaControlList)
{
    while (CaptchaControlList != NULL)
    {   
        CONTROL_NODE_DATA *p = CaptchaControlList->node_data;
        CaptchaControlList = CaptchaControlList->next;

        cpBody *body = *((cpBody**)(p->data));
        cpVect pos = cpBodyGetPosition(body);
        
        p->area.x = pos.x;p->area.y = -pos.y;

        p->angle = cpBodyGetAngle(body);
    }
}

