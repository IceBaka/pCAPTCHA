#ifndef GUI_H_
#define GUI_H_

#include <SDL.h>

typedef struct node
{
    void *data;
    struct node *next;
} Node;

Node JobList;
Node ButtonList;

typedef struct job_data
{
    ;
} JOB_DATA;

typedef struct button_data
{
    char* name;
    SDL_Rect area;
    void (*callback)(Uint32 state);
    void* data;
} BUTTON_DATA;

#endif /* GUI_H_ */