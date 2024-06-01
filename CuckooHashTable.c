#include "CuckooHashTable.h"

/*
Initializes a cuckoo hash table with two hash tables of the given size.
*/
void initalizeCuckooHashTable(cuckoo_hash_table c, int hash_table_size) {
    c->hash_table1 = malloc(sizeof(struct HashTable));
    assert(c->hash_table1 != NULL);
    initalizeHashTable(c->hash_table1, hash_table_size);

    c->hash_table2 = malloc(sizeof(struct HashTable));
    assert(c->hash_table2 != NULL);
    initalizeHashTable(c->hash_table2, hash_table_size);

    c->size = hash_table_size;
}

/*
Searches for a value in the specified hash table.
Returns the index if found, otherwise -1.
*/
int searchOnCuckooHashTable(phash_table t, int value) {
    int index = -1;
    for (int i = 0; i < t->size; i++) {
        if (t->value[i] == value) {
            index = i;
            break;
        }
    }
    return index;
}