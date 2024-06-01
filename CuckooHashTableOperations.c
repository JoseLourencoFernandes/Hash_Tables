#include "CuckooHashTable.c"
#include "HashFunctions.h"
#include <stdio.h>

/*
Inserts a key into the CUCKOO hash table using cuckoo hashing.
Prints status messages.
Returns 1 if the operation is successful, 0 otherwise.
*/
int ICUCKOO(cuckoo_hash_table cuckoo_table, int key) {
    // Check if the key already exists in either hash table
    if (searchOnCuckooHashTable(cuckoo_table->hash_table1, key) != -1 || searchOnCuckooHashTable(cuckoo_table->hash_table2, key) != -1) {
        printf("%d EXISTS\n", key);
        return 1;
    }

    int current_table = 0;
    int current_hash_index = hash_function1(key, cuckoo_table->size);
    int current_index = insertOnHashTable(cuckoo_table->hash_table1, key, current_hash_index);
    int current_key = key;

    // Try to insert into the first hash table
    if (current_index != -1) {
        printf("%d %d -> %d\nOK\n", 0, current_hash_index, current_key);
        return 1;
    }

    // Cuckoo hashing process
    for (int i = 0; i <= cuckoo_table->size; i++) {
        int next_table = (current_table + 1) % 2;
        int next_hash_index;
        int next_key;
        int next_index;

        // Determine next table, hash index, key, and index based on current table
        if (current_table == 0) {
            next_key = cuckoo_table->hash_table1->value[current_hash_index];
            next_hash_index = hash_function2(next_key, cuckoo_table->size);
            next_index = insertOnHashTable(cuckoo_table->hash_table2, next_key, next_hash_index);
        } else {
            next_key = cuckoo_table->hash_table2->value[current_hash_index];
            next_hash_index = hash_function1(next_key, cuckoo_table->size);
            next_index = insertOnHashTable(cuckoo_table->hash_table1, next_key, next_hash_index);
        }

        // If insertion is successful in the next table, print messages and return
        if (next_index != -1) {
            printf("%d %d -> %d\n", current_table, current_hash_index, current_key);
            printf("%d %d -> %d\nOK\n", next_table, next_index, next_key);
            // Update hash tables with inserted keys
            if (current_table == 0) {
                cuckoo_table->hash_table1->value[current_hash_index] = current_key;
                cuckoo_table->hash_table2->value[next_index] = next_key;
            } else {
                cuckoo_table->hash_table2->value[current_hash_index] = current_key;
                cuckoo_table->hash_table2->value[next_index] = next_key;
            }
            return 1;
        }

        // If insertion fails, update current table and prepare for next iteration
        if (current_table == 0) {
            cuckoo_table->hash_table1->value[current_hash_index] = current_key;
        } else {
            cuckoo_table->hash_table2->value[current_hash_index] = current_key;
        }

        // Print current status and update variables for next iteration
        printf("%d %d -> %d\n", current_table, current_hash_index, current_key);
        current_table = next_table;
        current_index = next_index;
        current_key = next_key;
        current_hash_index = next_hash_index;
    }
    
    // If maximum iterations reached, print failure message and return 0
    printf("GIVING UP!\n");
    return 0;
}

/*
Deletes a key from the CUCKOO hash table.
Prints "OK" if successful, "NO" otherwise.
*/
void DCUCKOO(cuckoo_hash_table cuckoo_table, int key) {
    int index;
    index = searchOnCuckooHashTable(cuckoo_table->hash_table1, key);
    if (index != -1) {
        cuckoo_table->hash_table1->value[index] = -1;
        printf("OK\n");
        return;
    }
    index = searchOnCuckooHashTable(cuckoo_table->hash_table2, key);
    if (index != -1) {
        cuckoo_table->hash_table2->value[index] = -1;
        printf("OK\n");
        return;
    }
    printf("NO\n");
}

/*
Searches for a key in the CUCKOO hash table.
Prints the table index and position if found, "NO" otherwise.
*/
void CCUCKOO(cuckoo_hash_table cuckoo_table, int key) {
    int index;
    index = searchOnCuckooHashTable(cuckoo_table->hash_table1, key);
    if (index != -1) {
        printf("%d %d\n", 0, index);
        return;
    }
    index = searchOnCuckooHashTable(cuckoo_table->hash_table2, key);
    if (index != -1) {
        printf("%d %d\n", 1, index);
        return;
    }
    printf("NO\n");
}

/*
Prints the content of the CUCKOO hash table.
*/
void PCUCKOO(cuckoo_hash_table cuckoo_table) {
    for (int i = 0; i < cuckoo_table->size; i++) {
        if (cuckoo_table->hash_table1->value[i] != -1) {
            printf("%d	%d	%d\n", 0, i, cuckoo_table->hash_table1->value[i]);
        }
    }
    for (int i = 0; i < cuckoo_table->size; i++) {
        if (cuckoo_table->hash_table2->value[i] != -1) {
            printf("%d	%d	%d\n", 1, i, cuckoo_table->hash_table2->value[i]);
        }
    }
}

/*
Reads input operations and processes them for the CUCKOO hash table.
*/
int processCUCKOO(cuckoo_hash_table cuckoo_hash_table) {
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
        controll = ICUCKOO(cuckoo_hash_table, key);
        break;
    case 'C':
        CCUCKOO(cuckoo_hash_table, key);
        break;
    case 'D':
        DCUCKOO(cuckoo_hash_table, key);
        break;
    case 'P':
        PCUCKOO(cuckoo_hash_table);
        break;
    default:
        break;
    }
    return controll;
 }