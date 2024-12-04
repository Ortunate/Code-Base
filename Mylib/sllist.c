#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/sllist.h"

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
    plist->head = NULL;
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
    if (plist->head == NULL) 
        plist->head = pnew;
    else{
        Node *scan = plist->head;
        while(scan->next!=NULL)
            scan=scan->next;
        scan->next=pnew;
    }
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
    plist->head = pc;
    Node *ps=pc;
    while(pc!=NULL){
        ps=pc;
        pc=pc->next;
        while(pc!=NULL && CompareItemAnd(item,pc->item)){
            count++;
            pt=pc;
            pc=pc->next;
            free(pt);
        }
        ps->next=pc;
    }
    #if COUNT == 1
    plist->size -= count;
    #endif
    return count;
}

bool InsertNode(List *plist, Item item, unsigned int pos){
    if(ListIsFull(plist) || pos > ListItemCount(plist))
        return false;
    Node *pnew=(Node *)malloc(sizeof(Node));
    if(pnew==NULL){
        fprintf(stderr,"Unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    CopyToNode(item, pnew);
    pnew->next=NULL;
    if(pos == 0){
        pnew->next=plist->head;
        plist->head=pnew;
    }
    else{
        Node *scan=plist->head;
        for(int i=0; i<pos-1; i++)
            scan=scan->next;
        pnew->next=scan->next;
        scan->next=pnew;
    }
    #if COUNT == 1
    plist->size++;
    #endif
    return true;
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
    return;
}