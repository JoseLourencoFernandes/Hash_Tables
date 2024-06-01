#ifndef CuckooHashTableDefine
#define CuckooHashTableDefine

#include "HashTable.h"

/*
Represents a cuckoo hash table with two hash tables.
*/
typedef struct CuckooHashTable {
    phash_table hash_table1;
    phash_table hash_table2;
    int size;
} *cuckoo_hash_table;

void initalizeCuckooHashTable(cuckoo_hash_table c, int hash_table_size);

int searchOnCuckooHashTable(phash_table t, int value);


#endif