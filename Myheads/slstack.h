#ifndef SLSTACK_H
#define SLSTACK_H
#include <stdbool.h>
//stack on single list
#define COUNT 0

//struct for storage
struct content {
    char c;
};

//seal
typedef struct content Item;
typedef struct node{
    Item item;
    struct node *next;
}Node;

typedef struct{
    #if COUNT==1
    unsigned int size;
    #endif
    Node *top;
}Stack;

//Initialize the stack
void InitializeStack(Stack *ps);

//Check if the stack is empty
bool StackIsEmpty(const Stack *ps);

//Push an item onto the stack
bool Push(Stack *ps, Item item);

//Pop an item from the stack
bool Pop(Stack *ps, Item *pitem);

//Empty the stack
void EmptyStack(Stack *ps);

//Count the number of items in the stack
unsigned int StackItemCount(const Stack *ps);


#endif