#include <stdio.h>
#include <SDL.h>
#include "gui.h"

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







/*==================================================================*/


/*==============================Button==============================*/

Node* addButton(Node** list,char* name,SDL_Rect area,void (*callback)(Uint32 state))
{
   Node* newNode = malloc(sizeof(Node));
   memset(newNode,0,sizeof(Node));
   newNode->data = malloc(sizeof(BUTTON_DATA));
   newNode->next = NULL;
   insertAreaNode(list,newNode);
   return newNode;
}





/*==================================================================*/