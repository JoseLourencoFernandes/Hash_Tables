#include "HashTable.c"
#include "HashFunctions.h"
#include <stdio.h>

/*
Inserts a key into the OPEN hash table using linear probing.
Prints status messages.
Returns 1 if the operation is successful, 0 otherwise.
*/
int IOPEN(phash_table hash_table, int key) {
    int hash_index = hash_function1(key, hash_table->size);
    if (searchOnHashTable(hash_table, hash_index, key) != -1) {
        printf("%d EXISTS\n", key);
        return 1;
    }

    int index = insertOrdenlyFromIndexOnHashTable(hash_table, key, hash_index);
    if (index == -1) {
        printf("GIVING UP!\n");
        return 0;
    } else {
        printf("%d -> %d\nOK\n", index, key);
    }
    return 1;
}

/*
Deletes a key from the OPEN hash table.
Prints "OK" if successful, "NO" otherwise.
*/
void DOPEN(phash_table hash_table, int key) {
    int hash_index = hash_function1(key, hash_table->size);
    int index = searchOnHashTable(hash_table, hash_index, key);
    if (index == -1) {
        printf("NO\n");
    } else {
        deleteFromHashTable(hash_table, index);
        printf("OK\n");
    }
}

/*
Searches for a key in the OPEN hash table.
Prints the index if found, "NO" otherwise.
*/
void COPEN(phash_table hash_table, int key) {
    int hash_index = hash_function1(key, hash_table->size);
    int index = searchOnHashTable(hash_table, hash_index, key);
    if (index == -1) {
        printf("NO\n");
    } else {
        printf("%d\n", index);
    }
}

/*
Prints the content of the OPEN hash table.
*/
void POPEN(phash_table hash_table) {
    for(int i = 0; i < hash_table->size; i++) {
        if (hash_table->value[i] > 0) {
            printf("%d	%d\n", i, hash_table->value[i]);
        } 
        if (hash_table->value[i] == -2) {
            printf("%d	D\n", i);
        } 
    }
}

/*
Reads input operations and processes them for the OPEN hash table.
*/
int processOPEN(phash_table hash_table) {
    char operation[20];
    char operator;
    int key;
    if (fgets(operation, sizeof(operation), stdin) == NULL) return 0;
    if (operation[0] == 'P') {
        if (sscanf(operation, "%c", &operator) != 1) return 0;
    } else {
        if (sscanf(operation, "%c %d", &operator, &key) != 2) return 0;
    }

    int controll = 1;
    switch (operator) {
    case 'I':
        controll = IOPEN(hash_table, key);
        break;
    case 'C':
        COPEN(hash_table, key);
        break;
    case 'D':
        DOPEN(hash_table, key);
        break;
    case 'P':
        POPEN(hash_table);
        break;
    default:
        break;
    }
    return controll;
 }