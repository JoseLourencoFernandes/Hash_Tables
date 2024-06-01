#ifndef LinkedListDefine
#define LinkedListDefine

#include <stdlib.h>

/*
Represents a node in the linked list.
*/
typedef struct Node {
    int value;
    struct Node *next;
} node;

/*
Represents a linked list with a pointer to the first node and the size of the list.
*/
typedef struct LinkedList {
    node *first;
    int size;
} *plinked_list;

void initalizeLinkedList(plinked_list l);

void insertOnLinkedList(plinked_list l, int value);

int searchOnLinkedList(plinked_list l, int value);

int deleteFromLinkedList(plinked_list l, int value);


#endif