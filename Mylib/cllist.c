#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/cllist.h"

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
        if(pn!=NULL){
            do{
                count++;
                pn=pn->next;
            }while(pn!=plist->head);
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
    if (plist->head == NULL) {
        plist->head = pnew;
        plist->tail = pnew;
        pnew->next = pnew;
    }
    else{
        plist->tail->next = pnew;
        plist->tail = pnew;
        plist->tail->next = plist->head;
    }
    #if COUNT == 1
        plist->size++;
    #endif
    return true;
}

void Traverse(const List *plist, void(*pfunc)(Item item)){
    Node *pn=plist->head;
    if(pn!=NULL){
        do{
            (*pfunc)(pn->item);
            pn=pn->next;
        }while(pn!=plist->head);
    }
}

void EmptyList(List *plist){
    Node *psave;
    if (plist->head != NULL) {
        plist->tail->next = NULL;
        while(plist->head!=NULL){
            psave = plist->head;
            plist->head = plist->head->next;
            free(psave);
        }
        plist->tail = NULL;
    }
    #if COUNT == 1
        plist->size = 0;
    #endif
}

unsigned int DeleteNode(List *plist, Item item){
    if(plist->head==NULL)
        return 0;
    if(plist->head==plist->tail){
        if(CompareItemAnd(item, plist->head->item)){
            EmptyList(plist);
            return 1;
        }
        else return 0;
    }
    Node *pc=plist->head, *ps=plist->tail;
    unsigned int count=0;
    do{
        if(CompareItemAnd(item, pc->item)){
            count++;
            if(pc==plist->head){
                plist->head=pc->next;
                ps->next=pc->next;
            }else{
                ps->next=pc->next;
                if(pc==plist->tail)
                    plist->tail=ps;
            }
            free(pc);
            pc=ps->next;
        }else{
            ps=pc;
            pc=pc->next;
        }
    }while(pc!=plist->head);
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