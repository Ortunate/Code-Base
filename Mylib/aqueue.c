#include <stdio.h>
#include "../Myheads/aqueue.h"

//api func

void InitializeQueue(Queue *pq){
    pq->front=0;
    pq->size=0;
}

bool QueueIsEmpty(const Queue *pq){
    return pq->size == 0;
}

bool QueueIsFull(const Queue *pq){
    return pq->size == MAXQUEUE;
}

bool EnQueue(Queue *pq, Item item){
    if(QueueIsFull(pq))
        return false;
    pq->items[pq->size]=item;
    pq->size++;
    return true;
}

bool DeQueue(Queue *pq, Item *pitem){
    if(QueueIsEmpty(pq))
        return false;
    *pitem=pq->items[pq->front];
    pq->front++;
    pq->size--;
    return true;
}

unsigned int QueueItemCount(const Queue *pq){
    return pq->size;
}