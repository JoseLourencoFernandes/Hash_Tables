#ifndef HashTableDefine
#define HashTableDefine

#include <stdlib.h>

/*
Represents a hash table with an array of integers.
*/
typedef struct HashTable {
    int *value;
    int size;
} *phash_table;

void initalizeHashTable(phash_table t, int hash_table_size);

int insertOnHashTable (phash_table hash_table, int value, int index);

int insertOrdenlyFromIndexOnHashTable(phash_table t, int value, int index);

void deleteFromHashTable(phash_table t, int index);

int searchOnHashTable(phash_table t, int value, int index);


#endif