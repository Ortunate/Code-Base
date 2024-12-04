#ifndef ASTACK_H
#define ASTACK_H
#include <stdbool.h>
//stack on array
#define MAXSTACK 100
#define COUNT 1
//struct for storage
struct content{
    char c;
};

//seal
typedef struct content Item;
typedef struct{
    int top;
    #if COUNT==1
    unsigned int size;
    #endif
    Item items[MAXSTACK];
}Stack;

//Initialize the stack
void InitializeStack(Stack *ps);

//Check if the stack is empty
bool StackIsEmpty(const Stack *ps);

//Check if the stack is full
bool StackIsFull(const Stack *ps);

//Push an item onto the stack
bool Push(Stack *ps, Item item);

//Pop an item from the stack
bool Pop(Stack *ps, Item *pitem);

//Empty the stack
void EmptyStack(Stack *ps);

#endif