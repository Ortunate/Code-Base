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
    int rear=(pq->front+pq->size)%MAXQUEUE;
    pq->items[rear]=item;
    pq->size++;
    return true;
}

bool DeQueue(Queue *pq, Item *pitem){
    if(QueueIsEmpty(pq))
        return false;
    *pitem=pq->items[pq->front];
    pq->front=(pq->front+1)%MAXQUEUE;
    pq->size--;
    return true;
}

unsigned int QueueItemCount(const Queue *pq){
    return pq->size;
}

void EmptyTheQueue(Queue *pq){
    pq->front=0;
    pq->size=0;
}

bool InsertItem(Queue *pq, Item item, unsigned int pos){
    if(QueueIsFull(pq) || pos > pq->size)
        return false;
    int i=(pq->front+pq->size-1)%MAXQUEUE;
    for(; i!=(pq->front+pos-1+MAXQUEUE)%MAXQUEUE; i=(i-1+MAXQUEUE)%MAXQUEUE)
        pq->items[(i+1)%MAXQUEUE]=pq->items[i];
    pq->items[(pq->front+pos)%MAXQUEUE]=item;
    pq->size++;
    return true;
}