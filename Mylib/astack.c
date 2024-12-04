#include <stdio.h>
#include "../Myheads/astack.h"


//api func

void InitializeStack(Stack *ps){
    ps->top=0;
    #if COUNT == 1
    ps->size = 0;
    #endif
}

bool StackIsEmpty(const Stack *ps){
    return ps->top == 0;
}

bool StackIsFull(const Stack *ps){
    return ps->top == MAXSTACK;
}

bool Push(Stack *ps, Item item){
    if(StackIsFull(ps))
        return false;
    ps->items[ps->top++]=item;
    #if COUNT == 1
    ps->size++;
    #endif
    return true;
}

bool Pop(Stack *ps, Item *pitem){
    if (StackIsEmpty(ps))
        return false;
    *pitem=ps->items[--ps->top];
    #if COUNT == 1
    ps->size--;
    #endif
    return true;
}

void EmptyStack(Stack *ps){
    ps->top=0;
    #if COUNT == 1
    ps->size=0;
    #endif
}