#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c=*key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % TABLE_SIZE;
}

void insert_table(hash_table table, char* key, char* value) {
    unsigned int index = hash(key);  /* Compute the index */
    insert_node(&table[index], key, value);  /* Pass a pointer to the node */
}

void* search_table(hash_table table, char* key) {
    unsigned int index = hash(key);  /* Compute the index */
    return search_linked(table[index], key);
}

void print_table(hash_table table) {
    int i = 0;
    for (i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            Node current = table[i];
            printf("Bucket %d:\n", i);
            while (current != NULL) {
                printf("  Key: %s, Value: %s\n", current->key, (char*)current->value);
                current = current->next;
            }
        }
    }
}

void free_table(hash_table table) {
    int i = 0;
    for (i = 0; i < TABLE_SIZE; i++) {
        if(table[i] != NULL) {
            freeList(table[i]);
        }
    }
}