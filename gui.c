#include <stdio.h>
#include <SDL.h>
#include "Chipmunk-7.0.3/include/chipmunk/chipmunk.h"
#include "gui.h"

Node *JobList;
Node *ControlList;

SDL_Window *APP_Window;
SDL_Renderer *APP_Renderer;

void appendNode(Node **head,Node *newNode)
{
    Node *p = *head;
    if (p != NULL)
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newNode;
    }
    else
    {
        *head = newNode;
    }
}

void deleteNode(Node **headP,Node *nodeToDel)
{
    Node *p = *headP;
    if (p == NULL || nodeToDel == NULL)return;
    if (nodeToDel == p)
    {
        *headP = p->next;
        free(nodeToDel);
        return;
    }
    while (p->next != NULL && p->next != nodeToDel)
    {
        p = p->next;
    }
    if (p->next == NULL)
    {
        return;
    }

    Node *q = p->next;
    p->next = q->next;
    free(q);
    return;
}

/*===============================JOB================================*/

Node* addJob(Node **list,void (*function)(void *data))
{
   Node* newNode=malloc(sizeof(Node));
   memset(newNode,0,sizeof(Node));
   newNode->node_data = malloc(sizeof(JOB_NODE_DATA));
   memset(newNode->node_data,0,sizeof(JOB_NODE_DATA));
   JOB_NODE_DATA *p = newNode->node_data;
   p->fun = function;
   p->data = NULL;

   newNode->next=NULL;
   appendNode(list,newNode);
   return newNode;
}

void deleteJob(Node **list,Node *nodeToDel)
{
    JOB_NODE_DATA *p = nodeToDel->node_data;
    free(p->data);
    free(nodeToDel->node_data);
    deleteNode(list,nodeToDel);
}

void RunJobs(Node *list)
{
    while (list != NULL)
    {   
        JOB_NODE_DATA *p = list->node_data;
        list = list->next;
        p->fun(p->data);

    }
    

}

/*==============================Control==============================*/

Node* addControl(Node **list,const char *name,SDL_Rect area,void (*callback)(Uint32 state,CONTROL_NODE_DATA *control_data),SDL_Texture *t_nohit,SDL_Texture *t_on,SDL_Texture *t_down)
{
    Node *newNode = malloc(sizeof(Node));
    memset(newNode,0,sizeof(Node));
    newNode->node_data = malloc(sizeof(CONTROL_NODE_DATA));
    memset(newNode->node_data,0,sizeof(CONTROL_NODE_DATA));
    CONTROL_NODE_DATA *p = newNode->node_data;
    p->name = name;
    p->area = area;
    p->callback = callback;
    p->texture_nohit = t_nohit;
    p->texture_on = t_on;
    p->texture_down = t_down;
    p->data = NULL;  // not use

    newNode->next = NULL;
    appendNode(list,newNode);
    return newNode;
}

void delControl(Node** list,Node* nodeToDel)
{
    CONTROL_NODE_DATA *p = nodeToDel->node_data;
    free(p->data);
    free(nodeToDel->node_data);
    deleteNode(list,nodeToDel);
}


/*==================================================================*/

void CheckMouse(Node *controlList)
{
    static int lock_flag = 0;

    if (!SDL_GetMouseState(NULL,NULL))lock_flag = 0;
    
    if (lock_flag == 1)return;
    
    if(SDL_GetMouseState(NULL,NULL))lock_flag = 1;

    while (controlList != NULL)
    {
        int x, y;
        Uint32 state = SDL_GetMouseState(&x, &y);;
        CONTROL_NODE_DATA *p=controlList->node_data;
        if (x >= p->area.x && x <= p->area.x + p->area.w)
        {
            if (y >= p->area.y && y <= p->area.y + p->area.h)
            {
                if (p->callback != NULL)
                {
                    //p->callback(state);
                    hitControl(state,p);
                }
                return;
            }
        }
        

        controlList = controlList->next;
    }
    

}

/*=============================Button===============================*/

void ButtonJob(void *data)
{
    struct data
    {
        Node *jobnode;
        CONTROL_NODE_DATA *control_data;
    } *d = data;

    SDL_Rect Brect=d->control_data->area;
    int x,y;
    if (!(SDL_BUTTON_LMASK & SDL_GetMouseState(&x, &y)))
    {
        if ((x >= Brect.x && x <= Brect.x + Brect.w) && (y >= Brect.y && y <= Brect.y + Brect.h))
        {
            d->control_data->callback(BUTTON_MOUSE_CLICK,d->control_data);
        }
        deleteJob(&JobList, d->jobnode);
    }
    else d->control_data->callback(BUTTON_MOUSE_DOWN,d->control_data);
}

void hitControl(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    struct data
    {
        Node *jobnode;
        CONTROL_NODE_DATA *control_data;
    } *d;

    if (SDL_BUTTON_LMASK&state)
    {
        Node *job = addJob(&JobList,ButtonJob);
        
        d = malloc(sizeof(struct data));
        d->jobnode = job;
        d->control_data = control_data;

        JOB_NODE_DATA *p=job->node_data;
        p->data=d;
    }
    else control_data->callback(BUTTON_MOUSE_ON,control_data);
}

void ButtonXXXHandler(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    if(state == BUTTON_MOUSE_ON)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_DOWN)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_CLICK)
    {
        ;
    }
}

void ButtonSayhiHandler(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    if(state == BUTTON_MOUSE_ON)
    {
        if(control_data->texture_on != NULL)SDL_RenderCopy(APP_Renderer,control_data->texture_on,NULL,&control_data->area);
    }
    else if(state == BUTTON_MOUSE_DOWN)
    {
        if(control_data->texture_down != NULL)SDL_RenderCopy(APP_Renderer,control_data->texture_down,NULL,&control_data->area);
    }
    else if(state == BUTTON_MOUSE_CLICK)
    {
        printf("hi");
    }
}

void topbarHandler(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    static int x = -1,y = -1;

    if(state == BUTTON_MOUSE_ON)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_DOWN)
    {
        int tempX,tempY,windowX,windowY;
        tempX=x;tempY=y;

        SDL_GetGlobalMouseState(&x, &y);
        if(tempX<0)return;
        SDL_GetWindowPosition(APP_Window,&windowX,&windowY);
        windowX+=(x-tempX);windowY+=(y-tempY);
        SDL_SetWindowPosition(APP_Window,windowX,windowY);
        
    }
    else if(state == BUTTON_MOUSE_CLICK)
    {
        x = -1,y = -1; 
    }
 
    
}


void CloseHandler(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    if(state == BUTTON_MOUSE_ON)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_DOWN)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_CLICK)
    {
        SDL_Delay(100);
        exit(0);
    }
}

void BlockHandler(Uint32 state,CONTROL_NODE_DATA *control_data)
{
    static int x = -1,y = -1;

    if(state == BUTTON_MOUSE_ON)
    {
        ;
    }
    else if(state == BUTTON_MOUSE_DOWN)
    {
        // int tempX,tempY,windowX,windowY;
        // tempX=x;tempY=y;

        // SDL_GetGlobalMouseState(&x, &y);
        // if(tempX<0)return;
        // control_data->area.x+=(x-tempX);control_data->area.y+=(y-tempY);

        int mouse_x,mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        cpVect pos = cpBodyGetPosition(*((cpBody**)(control_data->data)));
        cpBodySetVelocity(*((cpBody**)(control_data->data)),cpv((mouse_x-control_data->area.x)*10,-(mouse_y-control_data->area.y)*10));
    }
    else if(state == BUTTON_MOUSE_CLICK)
    {
        x = -1,y = -1;
    }
}



/*=============================Draw=================================*/

void drawControls(Node *controlList)
{
    while (controlList != NULL)
    {   
        CONTROL_NODE_DATA *p = controlList->node_data;
        controlList = controlList->next;
        if(p->texture_nohit != NULL)SDL_RenderCopyEx(APP_Renderer,p->texture_nohit,NULL,&p->area,p->angle,NULL,SDL_FLIP_NONE);
    }
}

// void draw_Bg()
// {
//     SDL_Rect dstRect={0,0,APP_WINDOW_W,APP_WINDOW_H};
//     SDL_RenderCopy(APP_Renderer,);
// }

// void draw_Bg_Win()
// {
//     SDL_RenderCopy(APP_Renderer,);
// }

// void draw_Bg_Lose()
// {
//     SDL_RenderCopy(APP_Renderer,);
// }


// void drawXXXButton(Uint32 state)
// {
//     if (state == BUTTON_MOUSE_NONE)
//     {
//         ;
//     }
//     else if (state == BUTTON_MOUSE_ON)
//     {
//         ;
//     }
//     else if (state == BUTTON_MOUSE_DOWN)
//     {
//         ;
//     }

// }

// void draw_CloseButton(Uint32 state)
// {
//     if (state == BUTTON_MOUSE_NONE)
//     {
//         ;
//     }
//     else if (state == BUTTON_MOUSE_ON)
//     {
//         ;
//     }
//     else if (state == BUTTON_MOUSE_DOWN)
//     {
//         ;
//     }
// }

// void draw_Eye()
// {

// }

// void drawCAPTCHA()
// {
//     draw_Bg();
//     draw_CloseButton();
//     draw_Refresh();
    
// }

/*==================================================================*/