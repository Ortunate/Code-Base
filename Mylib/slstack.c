#include <stdio.h>
#include <stdlib.h>
#include "../Myheads/slstack.h"

//api func

void InitializeStack(Stack *ps){
    ps->top=NULL;
    #if COUNT == 1
    ps->size=0;
    #endif
}

bool StackIsEmpty(const Stack *ps){
    return ps->top == NULL;
}

bool Push(Stack *ps, Item item){
    Node *pnew=(Node *)malloc(sizeof(Node));
    if(pnew == NULL)
        return false;
    pnew->item=item;
    pnew->next=ps->top;
    ps->top = pnew;
    #if COUNT == 1
    ps->size++;
    #endif
    return true;
}

bool Pop(Stack *ps, Item *pitem){
    if(StackIsEmpty(ps))
        return false;
    Node *pt=ps->top;
    *pitem=pt->item;
    ps->top=pt->next;
    free(pt);
    #if COUNT == 1
    ps->size--;
    #endif
    return true;
}

void EmptyStack(Stack *ps){
    Node *psave;
    while(ps->top != NULL){
        psave=ps->top;
        ps->top=psave->next;
        free(psave);
    }
    #if COUNT == 1
    ps->size=0;
    #endif
}

unsigned int StackItemCount(const Stack *ps){
    #if COUNT == 1
    return ps->size;
    #else
    unsigned int count=0;
    Node *pn=ps->top;
    while(pn!=NULL){
        count++;
        pn=pn->next;
    }
    return count;
    #endif
}