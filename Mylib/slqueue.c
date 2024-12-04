#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/slqueue.h"
//queue on list
//local func decl
static void CopyToNode(Item item, Node *pnode);
static void CopyToItem(Node *pnode, Item *pitem);

//api func

bool CompareItemAnd(const Item item0, const Item item1){//
    return item0.arrive == item1.arrive && item0.processtime == item1.processtime;
}

bool CompareItemOr(const Item item0, const Item item1){//
    return item0.arrive == item1.arrive || item0.processtime == item1.processtime;
}

void InitializeQueue(Queue *pq){
    pq->front=NULL;
    pq->rear=NULL;
    #if COUNT == 1
    pq->len = 0;
    #endif
}

bool QueueIsEmpty(const Queue *pq){
    #if COUNT == 1
    return pq->len == 0;
    #else
    return pq->front == NULL;
    #endif
}

bool QueueIsFull(const Queue *pq){
    #if COUNT == 1
    return pq->len == MAXQUEUELEN;
    #else
        Node *pt = (Node *)malloc(sizeof(Node));
        bool full = pt == NULL;
        free(pt);
        return full;
    #endif
}

unsigned int QueueItemCount(const Queue *pq){
    #if COUNT == 1
    return pq->len;
    #else
    unsigned int count = 0;
    Node *pn = pq->front;
    while (pn != NULL) {
        count++;
        pn = pn->next;
    }
    return count;
    #endif
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
    #if COUNT == 1
    pq->len++;
    #endif
    return true;
}

bool Dequeue(Queue *pq, Item *pitem){
    if(QueueIsEmpty(pq))
        return false;
    Node *pt = pq->front;
    CopyToItem(pt, pitem);
    pq->front=pq->front->next;
    free(pt);
    #if COUNT == 1
    pq->len--;
    #endif
    if (pq->front == NULL)
        pq->rear = NULL;
    return true;
}

void Traverse(const Queue *pq, void(*pfunc)(Item item)){
    Node *pn=pq->front;
    while(pn!=NULL){
        (*pfunc)(pn->item);
        pn=pn->next;
    }
}

void EmptyQueue(Queue *pq){
    Item dummy;
    while(!QueueIsEmpty(pq))
        Dequeue(pq, &dummy);
    #if COUNT == 1
    pq->len = 0;
    #endif
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
}

static void CopyToItem(Node *pnode, Item *pitem){
    *pitem=pnode->item;
}