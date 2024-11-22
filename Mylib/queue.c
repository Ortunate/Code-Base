#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/queue.h"

//local func decl
static void CopyToNode(Item item, Node *pnode);
static void CopyToItem(Node *pnode, Item *pitem);

//api func

bool CompareItemAnd(const Item item0, const Item item1){//
    if(item0.i==item1.i)
        return true;
    else
        return false;
}

bool CompareItemOr(const Item item0, const Item item1){//
    if(item0.i==item1.i)
        return true;
    else
        return false;
}

void InitializeQueue(Queue *pq){
    pq->front=NULL;
    pq->rear=NULL;
    pq->len=0;
}

bool QueueIsEmpty(const Queue *pq){
    return(pq->len==0);
}

bool QueueIsFull(const Queue *pq){
    return pq->len==MAXQUEUELEN;
}

unsigned int QueueItemCount(const Queue *pq){
    return pq->len;
}

bool Enqueue(Queue *pq, Item item){
    if(QueueIsFull(pq))
        return false;
    Node *pnew=(Node *)malloc(sizeof(Node));
    if(pnew==NULL){
        fprintf(stderr,"Unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    CopyToNode(item,pnew);
    pnew->next=NULL;

    if(QueueIsEmpty(pq))
        pq->front=pnew;
    else
        pq->rear->next=pnew;
    pq->rear=pnew;
    pq->len++;
    return true;
}

bool Dequeue(Queue *pq, Item *pitem){
    if(QueueIsEmpty(pq))
        return false;
    Node *pn, *pt=NULL;
    CopyToItem(pq->front,pitem);
    pt=pq->front;
    pq->front=pq->front->next;
    free(pt);
    if(!--pq->len)
        pq->rear=NULL;

    return true;
}

void Traverse(const Queue *pq, void(*pfunc)(Item item)){
    Node *pn=pq->front;
    while(pn!=NULL){
        (*pfunc)(pn->item);
        pn=pn->next;
    }
    return;
}

void EmptyQueue(Queue *pq){
    Item dummy;
    while(!QueueIsEmpty(pq))
        Dequeue(pq, &dummy);
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
    return;
}

static void CopyToItem(Node *pnode, Item *pitem){
    *pitem=pnode->item;
    return;
}