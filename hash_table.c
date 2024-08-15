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

void insert_table(hash_table table, char* key, void* value) {
    unsigned int index = hash(key);  /* Compute the index */
    insert_node(&table[index], key, value);  /* Pass a pointer to the node */
}

void* search_table(hash_table table, char* key) {
    unsigned int index = hash(key);  /* Compute the index */
    return search_linked(table[index], key);
}

int is_in_table(hash_table table, char* key) {
    if (search_table(table, key) !=0) {
        return 1;
    }
    return 0;
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

void update_table_value(hash_table table, char* key, char* new_value) {
    unsigned int index = hash(key);
    Node temp = table[index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            temp->value = new_value;
            return;
        }
        temp = temp->next;
    }

    printf("Error: Key '%s' not found in the table\n", key);
}


void free_table(hash_table table) {
    int i = 0;
    for (i = 0; i < TABLE_SIZE; i++) {
        if(table[i] != NULL) {
            freeList(table[i]);
        }
    }
}