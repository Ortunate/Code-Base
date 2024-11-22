#include<stdio.h>
#include<stdlib.h>
#include"../Myheads/list.h"

//local func decl
static void CopyToNode(Item item, Node *pnode);

//api func

bool CompareItemAnd(const Item item0, const Item item1){//
    if(item0.c==item1.c)
        return true;
    else
        return false;
}

bool CompareItemOr(const Item item0, const Item item1){//
    if(item0.c==item1.c)
        return true;
    else
        return false;
}

void InitializeList(List *plist){
    *plist=NULL;
}

bool ListIsEmpty(const List *plist){
    return(*plist==NULL)?true:false;
}

bool ListIsFull(const List *plist){
    Node *pt=(Node *)malloc(sizeof(Node));
    bool full=(pt==NULL)?true:false;
    free(pt);
    return full;
}

unsigned int ListItemCount(const List *plist){
    unsigned int count=0;
    Node *pn=*plist;
    while(pn!=NULL){
        count++;
        pn=pn->next;
    }
    return count;
}

bool AddItem(List *plist, Item item){
    Node *scan=*plist;
    Node *pnew=(Node *)malloc(sizeof(Node));
    if (pnew==NULL)
        return false;
    CopyToNode(item, pnew);
    pnew->next=NULL;
    if(scan==NULL)
        *plist=pnew;
    else{
        while(scan->next!=NULL)
            scan=scan->next;
        scan->next=pnew;
    }
    return true;
}

void Traverse(const List *plist, void(*pfunc)(Item item)){
    Node *pn=*plist;
    while(pn!=NULL){
        (*pfunc)(pn->item);
        pn=pn->next;
    }
    return;
}

void EmptyList(List *plist){
    Node *psave;
    while(*plist!=NULL){
        psave=(*plist)->next;
        free(*plist);
        *plist=psave;
    }
    return;
}

unsigned int DeleteNode(List *plist, Item item){
    Node *pc=*plist, *pt=NULL;
    int count=0;
    while(CompareItemAnd(item,pc->item) && pc!=NULL){
        count++;
        pt=pc;
        pc=pc->next;
        free(pt);
        pt=NULL;
    }
    *plist=pc;
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
    return count;
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
    return;
}