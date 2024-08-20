#include "../Headers/symbol_struct.h"

enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table) {
    Symbol new_symbol;
    new_symbol = (Symbol)handel_malloc(sizeof(struct symbol));
    /*Check if the symbol already exists in the table and has a count of 0*/
    if ((is_in_table(symbol_table, symbol_name) && new_symbol->count == 0)) return firstPassError_symbol_name_taken;

    if (type_flag == DATA_FLAG) {
        new_symbol->count = DC; /*Use the data counter (DC) for data symbols*/
    }
    if (type_flag == OPCODE_FLAG) {
        new_symbol->count = IC+100; /*Use the instruction counter (IC) + offset for opcode symbols*/
    }
    if (type_flag == EXTERN_FLAG) {
        new_symbol->count = 0;  /*External symbols have a count of 0*/
    }
    new_symbol->flag = type_flag;

    insert_table(symbol_table, symbol_name, new_symbol);

    return Error_Success;
}

enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name) {
    Symbol symbol = search_table(symbol_table, symbol_name);
    if (symbol != NULL) {
        return symbol->flag;
    }
    return -1;
}

enum symbol_flag get_symbol_count(hash_table symbol_table, char *symbol_name) {
    Symbol symbol = search_table(symbol_table, symbol_name);
    if (symbol != NULL) {
        return symbol->count;
    }
    return -1;
}

void update_symbol_flag(hash_table symbol_table, char *symbol_name, enum symbol_flag new_symbol_flag) {
    Symbol symbol = search_table(symbol_table, symbol_name);
    symbol->flag = new_symbol_flag;
}