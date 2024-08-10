#include "symbole_table.h"
/* Hash function to calculate the index */
unsigned int hash(const char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % size;
}

/* Create a new symbol table */
symbol_table* create_symbol_table() {
    symbol_table* table = (symbol_table*)malloc(sizeof(symbol_table));
    table->size = TABLE_SIZE;
    table->buckets = (SymbolNode**)calloc(TABLE_SIZE, sizeof(SymbolNode*));
    return table;
}

/* Insert a new label into the symbol table */
void insert_label(symbol_table* table, const char* label_name, int assembly_line, int is_data_line) {
    unsigned int index = hash(label_name, table->size);
    SymbolNode* new_node = handle_malloc(sizeof(SymbolNode));
    strncpy(new_node->label.label_name, label_name, MAX_LABEL_LENGTH);
    new_node->label.assembly_line = assembly_line;
    new_node->label.is_data_line = is_data_line;

    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

/* Search for a label in the symbol table */
label_address* search_label(symbol_table* table, const char* label_name) {
    unsigned int index = hash(label_name, table->size);
    SymbolNode* node = table->buckets[index];
    while (node) {
        if (strncmp(node->label.label_name, label_name, MAX_LABEL_LENGTH) == 0) {
            return &node->label;
        }
        node = node->next;
    }
    return NULL;
}

/* Free the symbol table */
void free_symbol_table(symbol_table* table) {
    size_t i;
    for (i = 0; i < table->size; i++) {
        SymbolNode* node = table->buckets[i];
        while (node) {
            SymbolNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}