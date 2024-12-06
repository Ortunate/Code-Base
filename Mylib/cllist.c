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
    plist->head=plist->tail=NULL;
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
        if(pn){
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
    if (!pnew){
        printf("Unable to allocate memory\n");
        return false;
    }
    CopyToNode(item, pnew);
    if(!plist->head){
        plist->head=pnew;
        plist->tail=pnew;
        pnew->next=pnew;
    }else{
        plist->tail->next=pnew;
        plist->tail=pnew;
        pnew->next=plist->head;
    }
    #if COUNT == 1
    plist->size++;
    #endif
    return true;
}

void Traverse(const List *plist, void(*pfunc)(Item item)){
    Node *pn=plist->head;
    if(pn){
        do{
            (*pfunc)(pn->item);
            pn=pn->next;
        }while(pn!=plist->head);
    }
}

void EmptyList(List *plist){
    Node *psave;
    if (plist->head){
        plist->tail->next = NULL;
        while(plist->head){
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
    if(!plist->head)
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
    if(plist->head == NULL)
        plist->tail=NULL;
    #if COUNT == 1
    plist->size -= count;
    #endif
    return count;
}

bool InsertNode(List *plist, Item item, unsigned int pos){
    if(ListIsFull(plist))
        return false;
    if(ListIsEmpty(plist) || pos>ListItemCount(plist)){
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
    if(pos){
        Node *scan=plist->head;
        for(int i=0; i<pos-1; i++)
            scan=scan->next;
        pnew->next=scan->next;
        scan->next=pnew;
        if(scan == plist->tail)
            plist->tail=pnew;
    }else{
        pnew->next=plist->head;
        plist->head=pnew;
        plist->tail->next=pnew;
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
    do{
        if(CompareItemAnd(item,pc->item)){
            *pn=pc;
            return true;
        }
        pc=pc->next;
    }while(pc!=plist->head);
    return false;
}

void ShowList(const List *plist){
    if(!plist->head){
        printf("The list is empty.\n");
        return;
    }
    Node *pn=plist->head;
    int i=0;
    do{
        printf("%d: %c \n", i++, pn->item.c);
        pn=pn->next;
    }while(pn!=plist->head);
    printf("\n");
}


//static func
static void CopyToNode(Item item, Node *pnode){
    pnode->item=item;
}