#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned int hash(const char* key, size_t size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % size;
}

HashTable* create_hash_table(size_t size) {
    HashTable* table;
    table = handle_malloc(sizeof(HashNode*));
    table->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    if (table->buckets == NULL) {
        fprintf(stderr, "Hash table buckets allocation failed\n");
        free(table);
        exit(1);
    }
    table->size = size;
    return table;
}

void insert_table(HashTable* table, const char* key, const char* value) {
    unsigned int index = hash(key, table->size);
    HashNode* new_node;
    new_node = handle_malloc(sizeof(HashNode));
    strncpy(new_node->key, key, MAX_MACRO_NAME_LENGTH);
    new_node->value = strdup(value);
    if (new_node->value == NULL) {
        fprintf(stderr, "Value allocation failed\n");
        free(new_node);
        exit(1);
    }
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

char* search_table(HashTable* table, const char* key) {
    unsigned int index;
    HashNode* node;
    index = hash(key, table->size);
    node = table->buckets[index];
    while (node) {
        if (strncmp(node->key, key, MAX_MACRO_NAME_LENGTH) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void free_hash_table(HashTable* table) {
    size_t i;
    for (i = 0; i < table->size; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->value);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}