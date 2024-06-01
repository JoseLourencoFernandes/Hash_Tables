#include "HashTable.h"
#include <assert.h>

/*
Initializes the hash table with a given size.
Allocates memory for the array and sets all values to -1.
*/
void initalizeHashTable(phash_table t, int hash_table_size) {
    t->value = malloc(hash_table_size*sizeof(int));
    assert(t->value != NULL);
    for (int i = 0; i < hash_table_size; i++) {
        t->value[i] = -1;
    }
    t->size = hash_table_size;
}

/*
Inserts a value into the hash table given the index.
Returns the index where the value was inserted or -1 if it was not possible to insert it.
*/
int insertOnHashTable (phash_table hash_table, int value, int index) {
    if (hash_table->value[index] == -1) {
        hash_table->value[index] = value;
        return index;
    } 
    return -1;
}

/*
Inserts a value into the hash table from a specified index in an orderly cyclic manner.
If the index or its subsequent positions are available, the value is inserted there.
If not, it tries to insert from the beginning of the table.
Returns the index where the value was inserted or -1 if it was not possible to insert it.
*/
int insertOrdenlyFromIndexOnHashTable(phash_table t, int value, int index) {
    for(int i = index; i < t->size; i++) {
        if (t->value[i] < 0) {
            t->value[i] = value;
            return i;
        }
    }
    for(int i = 0; i < index ; i++) {
        if (t->value[i] < 0) {
            t->value[i] = value;
            return i;
        }
    }
    return -1;
}

/*
Deletes the value at the specified index in the hash table by marking it as a tombstone (value -2).
*/
void deleteFromHashTable(phash_table t, int index) {
    t->value[index] = -2;
}

/*
Searches for a value in the hash table starting from a specified index.
If the value is found, its index is returned.
If not found, and a tombstone (value -2) exists, the value is moved to that index, and the original index is marked as -2.
*/
int searchOnHashTable(phash_table t, int initial_index, int value) {
    int index = -1;
    int index_tombstone = -1;
    int found_tombstone = -1;
    int breaked = 0;
    for (int i = initial_index; i < t->size; i++) {
        if (t->value[i] == value) {
            index = i;
            breaked = 1;
            break;
        }
        if (t->value[i] == -2 && found_tombstone == -1) {
            index_tombstone = i;
            found_tombstone = 1;
        }
    }
    if (!breaked) {
        for (int i = 0; i < initial_index; i++) {
            if (t->value[i] == value) {
                index = i;
                break;
            }
            if (t->value[i] == -2 && found_tombstone == -1) {
                index_tombstone = i;
                found_tombstone = 1;
            }
        }
    }
    if (index != -1 && index_tombstone != -1) {
        t->value[index_tombstone] = value;
        deleteFromHashTable(t, index);
        index = index_tombstone;
    }
    return index;
}