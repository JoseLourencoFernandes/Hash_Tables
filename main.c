#include "OpenHashTableOperations.c"
#include "LinkHashTableOperations.c"
#include "CuckooHashTableOperations.c"
#include "HashFunctions.c"
#include <string.h>
#include <assert.h>


int main() {
    int controll = 1;
    int hash_table_size;
    char buf[BUFSIZ];
    char hash_table_type_string[7];

    //Reads input to determine the type and size of the hash table.
    assert(scanf("%d\n", &hash_table_size) == 1);
    assert(fgets(buf, BUFSIZ, stdin) != NULL);
    assert(buf[strlen(buf) - 1] == '\n');
    sscanf(buf, "%s", hash_table_type_string);

    //Initializes and processes hash table operations based on the type.
    if (strcmp(hash_table_type_string, "OPEN") == 0) {
        phash_table hash_table = malloc(sizeof(phash_table));
        assert(hash_table != NULL);
        initalizeHashTable(hash_table, hash_table_size);
        while(controll) {
            controll = processOPEN(hash_table);
        }
    } else 
    
        if (strcmp(hash_table_type_string, "LINK") == 0) {
        plinked_list *hash_table = malloc(hash_table_size * sizeof(plinked_list));
        assert(hash_table != NULL);
        for (int i = 0; i < hash_table_size; i++) {
            hash_table[i] = malloc(sizeof(struct LinkedList));
            assert(hash_table[i] != NULL);
            initalizeLinkedList(hash_table[i]);
        }
        while(controll) {
            controll = processLINK(hash_table, hash_table_size);
        }
    } else 
    
        if (strcmp(hash_table_type_string, "CUCKOO") == 0) {
        cuckoo_hash_table cuckoo_hash_table = malloc(hash_table_size * sizeof(cuckoo_hash_table));
        assert(cuckoo_hash_table != NULL);
        initalizeCuckooHashTable(cuckoo_hash_table, hash_table_size);
        while(controll) {
            controll = processCUCKOO(cuckoo_hash_table);
        }
    }

    return 0;
}