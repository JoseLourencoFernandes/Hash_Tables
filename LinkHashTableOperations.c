#include "LinkedList.c"
#include "HashFunctions.h"
#include <stdio.h>

/*
Inserts a key into the LINK hash table using linked lists.
Prints status messages.
*/
void ILINK(plinked_list hash_table[], int hash_table_size, int key) {
    int index = hash_function1(key, hash_table_size);
    if(searchOnLinkedList(hash_table[index], key) != -1) {
        printf("%d EXISTS\n", key);
        return;
    }
    insertOnLinkedList(hash_table[index], key);
    printf("%d -> %d\nOK\n", index, key);
}

/*
Deletes a key from the LINK hash table.
Prints "OK" if successful, "NO" otherwise.
*/
void DLINK(plinked_list hash_table[], int hash_table_size, int key) {
    int index = hash_function1(key, hash_table_size);
    if (searchOnLinkedList(hash_table[index], key) != -1) {
        deleteFromLinkedList(hash_table[index], key);
        printf("OK\n");
        return;
    }
    printf("NO\n");
}

/*
Searches for a key in the LINK hash table.
Prints the index if found, "NO" otherwise.
*/
void CLINK(plinked_list hash_table[], int hash_table_size, int key) {
    int index = hash_function1(key, hash_table_size);
    if (searchOnLinkedList(hash_table[index], key) != -1) {
        printf("%d\n", index);
        return;
    }
    printf("NO\n");
}

/*
Prints the content of the LINK hash table.
*/
void PLINK(plinked_list hash_table[], int hash_table_size) {
    for(int i = 0; i < hash_table_size; i++) {
        if (hash_table[i]->first != NULL) {
            printf("%d ", i);
            node *aux = hash_table[i]->first;
            for (; aux->next != NULL; aux = aux->next) {
                printf("%d ", aux->value);
            }
            printf("%d", aux->value);
            printf("\n");
        }
    }
}

/*
Reads input operations and processes them for the LINK hash table.
*/
int processLINK(plinked_list hash_table[], int hash_table_size) {
    char operation[20];
    char operator;
    int key;
    if (fgets(operation, sizeof(operation), stdin) == NULL) return 0;
    if (operation[0] == 'P') {
        if (sscanf(operation, "%c", &operator) != 1) return 0;
    } else {
        if (sscanf(operation, "%c %d", &operator, &key) != 2) return 0;
    }

    switch (operator) {
    case 'I':
        ILINK(hash_table, hash_table_size, key);
        break;
    case 'C':
        CLINK(hash_table, hash_table_size, key);
        break;
    case 'D':
        DLINK(hash_table, hash_table_size, key);
        break;
    case 'P':
        PLINK(hash_table, hash_table_size);
        break;
    default:
        break;
    }
    return 1;
 }