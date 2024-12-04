#ifndef SLQUEUE_H
#define SLQUEUE_H
#include<stdbool.h>

#define COUNT 1
#define MAXQUEUELEN 10
//queue on sllist

typedef struct item{
    long arrive;
    int processtime;
}Item;

typedef struct node{
    Item item;
    struct node *next;
}Node;
typedef struct queue{
    #if COUNT == 1
    unsigned int len;
    #endif
    Node *front;
    Node *rear;
}Queue;

//function declarations
//change all 'list' to queue
//Op:compare &&
bool CompareItemAnd(const Item item0, const Item item1);

//Op:compare ||
bool CompareItemOr(const Item item0, const Item item1);

//Operation: initialize a List
//Precondition: plist is a List* not NULL
//Postcondition:List initialized as null
void InitializeQueue(Queue *pq);

//Op:judge a list empty or not
//Pre:plist
//post:return true or F
bool QueueIsEmpty(const Queue *pq);

//Op:judge a list full or not
//Pre:plist
//Post:return T or F
bool QueueIsFull(const Queue *pq);

//Op:confirm the number of elements
//Pre:plist
//Post:return the number
unsigned int QueueItemCount(const Queue *pq);

//Op:add an item
//Post:T or F
bool Enqueue(Queue *pq, Item item);

//Op:do Func to every element
void Traverse(const Queue *pq, void(*pfunc)(Item item));

//Op:free memories
void EmptyQueue(Queue *pq);

//Op:dequeue
bool Dequeue(Queue *pq, Item *pitem);

#endif