#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/dllist.h"

//local func decl
static void CopyToNode(Item item, Node *pnode);

//api func

bool CompareItemAnd(const Item item0, const Item item1){//
    return item0.c == item1.c;
}

bool CompareItemOr(const Item item0, const Item item1){//
    return item0.c == item1.c;
}

void InitializeList(List *plist){
    plist->head = plist->tail = NULL;
    #if COUNT == 1
    plist->size = 0;
    #endif
}

bool ListIsEmpty(const List *plist){
    return plist->head == NULL;
}

bool ListIsFull(const List *plist){
    Node *pt=(Node *)malloc(sizeof(Node));
    bool full=pt==NULL;
    free(pt);
    return full;
}

unsigned int ListItemCount(const List *plist){
    #if COUNT == 1
    return plist->size;
    #else
        unsigned int count=0;
        Node *pn=plist->head;
        while(pn!=NULL){
            count++;
            pn=pn->next;
        }
        return count;
    #endif
}

bool AddItem(List *plist, Item item){
    Node *pnew=(Node *)malloc(sizeof(Node));
    if (pnew==NULL)
        return false;
    CopyToNode(item, pnew);
    pnew->next=NULL;
    pnew->prev=plist->tail;
    if (plist->head == NULL) 
        plist->head=pnew;
    else
        plist->tail->next=pnew;
    plist->tail=pnew;
    #if COUNT == 1
    plist->size++;
    #endif
    return true;
}

void Traverse(const List *plist, void(*pfunc)(Item item)){
    Node *pn=plist->head;
    while(pn!=NULL){
        (*pfunc)(pn->item);
        pn=pn->next;
    }
    return;
}

void EmptyList(List *plist){
    Node *psave;
    while(plist->head!=NULL){
        psave = plist->head;
        plist->head = plist->head->next;
        free(psave);
    }
    plist->tail = NULL;
    #if COUNT == 1
    plist->size = 0;
    #endif
}

unsigned int DeleteNode(List *plist, Item item){
    if(plist->head==NULL)
        return 0;
    Node *pc=plist->head, *pt=NULL;
    unsigned int count=0;

    while(pc!=NULL && CompareItemAnd(item,pc->item)){
        count++;
        pt=pc;
        pc=pc->next;
        free(pt);
    }
    if(pc==NULL){
        plist->tail=NULL;
        return count;
    }
    else
        pc->prev=NULL;
    plist->head = pc;
    while(pc!=NULL){
        if(CompareItemAnd(item, pc->item)){
            count++;
            pc->prev->next=pc->next;
            if(pc->next != NULL)
                pc->next->prev=pc->prev;
            else
                plist->tail=pc->prev;
            pt=pc;
            pc=pc->next;
            free(pt);
        }else
            pc=pc->next;
    }
    #if COUNT == 1
    plist->size -= count;
    #endif
    return count;
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
    return;
}