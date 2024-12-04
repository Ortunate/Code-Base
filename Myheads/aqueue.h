#ifndef AQUEUE_H
#define AQUEUE_H
#include <stdbool.h>
//queue on arr
#define MAXQUEUE 100

typedef struct item{
    char c;
}Item;

typedef struct{
    int front, size;
    Item items[MAXQUEUE];
}Queue;

//Initialize the queue
void InitializeQueue(Queue *pq);

//Check if empty
bool QueueIsEmpty(const Queue *pq);

//Check if full
bool QueueIsFull(const Queue *pq);

//Add an item
bool EnQueue(Queue *pq, Item item);

//Remove an item
bool DeQueue(Queue *pq, Item *pitem);

//Get the number
unsigned int QueueItemCount(const Queue *pq);

#endif