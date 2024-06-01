#include "LinkedList.h"

/*
Initializes a linked list by setting its first node to NULL and size to 0.
*/
void initalizeLinkedList(plinked_list l) {
    l->first = NULL;
    l->size = 0;
}

/*
Inserts a new node with the given value at the beginning of the linked list.
*/
void insertOnLinkedList(plinked_list l, int value) {
    node *new = malloc(sizeof(node));
    assert(new != NULL);

    new->value = value;
    new->next = l->first;
    l->first = new; 
    l->size++;
}

/*
Searches for a value in the linked list.
Returns 1 if found, otherwise -1.
*/
int searchOnLinkedList(plinked_list l, int value) {
    node *aux = l->first;
    for (int i = 0; i < l->size; i++) {
        if (aux->value == value) return 1;
        aux = aux->next;
    }
    return -1;
}

/*
Deletes a node with the given value from the linked list if it exists.
Returns 1 if the deletion is successful, 0 otherwise.
*/
int deleteFromLinkedList(plinked_list l, int value) {
    node *current = l->first;
    node *prev = NULL;

    if (current == NULL) {
        return 0;
    }
    
    if (current->value == value) {
        l->first = current->next;
        l->size--;
        free(current);
        return 1;
    }

    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        return 0;
    }
    prev->next = current->next;
    l->size--;
    free(current);
    return 1;
}