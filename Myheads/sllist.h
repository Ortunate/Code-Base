#ifndef SLLIST_H
#define SLLIST_H
#include<stdbool.h>

#define COUNT 0
//struct for storage
struct content{
    char c;
};

//seal
typedef struct content Item;
typedef struct node{
    Item item;
    struct node *next;
}Node;

typedef struct{
    Node *head;
    #if COUNT==1
    unsigned int size;
    #endif
}List;


//function declarations

//Op:compare &&
bool CompareItemAnd(const Item item0, const Item item1);

//Op:compare ||
bool CompareItemOr(const Item item0, const Item item1);

//Operation: initialize a List
//Precondition: plist is a List* not NULL
//Postcondition:List initialized as null
void InitializeList(List *plist);

//Op:judge a list empty or not
//Pre:plist
//post:return true or F
bool ListIsEmpty(const List *plist);

//Op:judge a list full or not
//Pre:plist
//Post:return T or F
bool ListIsFull(const List *plist);

//Op:confirm the number of elements
//Pre:plist
//Post:return the number
unsigned int ListItemCount(const List *plist);

//Op:add an item
//Post:T or F
bool AddItem(List *plist, Item item);

//Op:do Func to every element
void Traverse(const List *plist, void(*pfunc)(Item item));

//Op:free memories
void EmptyList(List *plist);

//Op:delete
unsigned int DeleteNode(List *plist, Item item);

#endif