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

int Sequence(const Node *pn0, const Node *pn1){//
    return pn0->item.c - pn1->item.c;
}


void InitializeList(List *plist){
    plist->head=NULL;
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
        while(pn){
            count++;
            pn=pn->next;
        }
        return count;
    #endif
}

bool AddItem(List *plist, Item item){
    Node *pnew=(Node *)malloc(sizeof(Node));
    if (!pnew){
        printf("Unable to allocate memory\n");
        return false;
    }
    CopyToNode(item, pnew);
    pnew->next=NULL;
    if (!plist->head) 
        plist->head=pnew;
    else{
        Node *scan=plist->head;
        while(scan->next)
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
    while(pn){
        (*pfunc)(pn->item);
        pn=pn->next;
    }
    return;
}

void EmptyList(List *plist){
    Node *psave;
    while(plist->head){
        psave=plist->head;
        plist->head=plist->head->next;
        free(psave);
    }
    #if COUNT == 1
    plist->size = 0;
    #endif
}

unsigned int DeleteItem(List *plist, Item item){
    if(!plist->head)
        return 0;
    Node *pc=plist->head, *pt=NULL;
    unsigned int count=0;
    while(pc && CompareItemAnd(item,pc->item)){
        count++;
        pt=pc;
        pc=pc->next;
        free(pt);
    }
    plist->head=pc;
    Node *ps=pc;
    while(pc){
        ps=pc;
        pc=pc->next;
        while(pc && CompareItemAnd(item,pc->item)){
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
    if(ListIsFull(plist))
        return false;
    if(ListIsEmpty(plist) || pos > ListItemCount(plist)){
        AddItem(plist, item);
        return true;
    }
    Node *pnew=(Node *)malloc(sizeof(Node));
    if(!pnew){
        fprintf(stderr,"Unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    CopyToNode(item, pnew);
    pnew->next=NULL;
    if(!pos){
        pnew->next=plist->head;
        plist->head=pnew;
    }else{
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

bool SearchNode(const List *plist, Node **pn, Item item){
    if(!plist->head){
        printf("The list is empty.\n");
        return false;
    }
    Node *pc=plist->head;
    while(pc){
        if(CompareItemAnd(item,pc->item)){
            *pn=pc;
            return true;
        }
        pc=pc->next;
    }
    return false;
}

void ShowList(const List *plist){
    if(!plist->head){
        printf("The list is empty.\n");
        return;
    }
Node *pn=plist->head;
    for(int i=0; pn; pn=pn->next, i++)
        printf("%d: %c \n", i, pn->item.c);
    printf("\n");
}

void ReverseList(List *plist){
    if(!plist->head)
        return;
    Node *pc=plist->head, *ps=NULL, *pnext;
    while(pc){
        pnext=pc->next;
        pc->next=ps;
        ps=pc;
        pc=pnext;
    }
    plist->head->next=NULL;
    plist->head=ps;
}

void SortList(List *plist){
    if(ListItemCount(plist)<2)
        return;
    Node *p1=plist->head, *p2, *pmin;
    Item temp;
    while(p1){
        pmin=p1;
        p2=p1->next;
        while(p2){
            if(Sequence(p2,pmin)<0)
                pmin=p2;
            p2=p2->next;
        }
        temp=p1->item;
        p1->item=pmin->item;
        pmin->item=temp;
        p1=p1->next;
    }
}

//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
}