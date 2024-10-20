#ifndef GUI_H_
#define GUI_H_

#include <SDL.h>

#define APP_WINDOW_W 640
#define APP_WINDOW_H 395 //640*0.618

typedef struct node
{
    void *node_data;
    struct node *next;
} Node;

extern Node *JobList;
extern Node *ControlList;

extern SDL_Window *APP_Window;
extern SDL_Renderer *APP_Renderer;

typedef struct job_node_data
{
    void (*fun)(void *data);
    void *data;
} JOB_NODE_DATA;

typedef struct control_node_data
{
    const char *name;
    SDL_Rect area;
    double angle;   // todo: check angle in some functions
    void (*callback)(Uint32 state,struct control_node_data *control_data);

    SDL_Texture *texture_nohit;
    SDL_Texture *texture_on;
    SDL_Texture *texture_down;

    void *data;
} CONTROL_NODE_DATA;

#define BUTTON_MOUSE_NONE   0
#define BUTTON_MOUSE_ON     1
#define BUTTON_MOUSE_DOWN   2
#define BUTTON_MOUSE_CLICK  3 // down area == up area

Node* addControl(Node **list,const char *name,SDL_Rect area,void (*callback)(Uint32 state,CONTROL_NODE_DATA *control_data),SDL_Texture *t_nohit,SDL_Texture *t_on,SDL_Texture *t_down);
void CheckMouse(Node *controlList);
void RunJobs(Node *list);
void hitControl(Uint32 state,CONTROL_NODE_DATA *control_data);
void drawControls(Node *controlList);

void ButtonSayhiHandler(Uint32 state,CONTROL_NODE_DATA *control_data);
void topbarHandler(Uint32 state,CONTROL_NODE_DATA *control_data);
void CloseHandler(Uint32 state,CONTROL_NODE_DATA *control_data);
void BlockHandler(Uint32 state,CONTROL_NODE_DATA *control_data);

#endif /* GUI_H_ */