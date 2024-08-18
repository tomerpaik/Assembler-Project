#include "first_pass.h"
int DC = 0;
int IC = 0;

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LABEL_LENGTH];
    int error_found = 0;
    enum project_error current_error = 0;
    int symbol_flag, offset, after_label_offset=0, line_num = 0;
    char * first_word_copy = 0;
    char * substring_symbol_copy = 0;
    EntryExternContent content;
    am_file = open_new_file(am_path, ".am", "r");
    /* Initialize  symbol table */
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        if (is_comment_empty_line(line)) continue; /*IF line is a comment or a empty sentence SKIP to the next line*/
        /*initial variables*/
        symbol_flag = 0;
        offset = 0;
        sscanf(line, "%s%n", first_word, &offset);
        /*
        printf("line: %d, first word: %s\n", line_num, first_word);
        */
        /*check if word is a symbol*/
        if (first_word[strlen(first_word) - 1] == ':') {
            first_word_copy = my_strdup(first_word);
            substring_symbol_copy = substring(first_word_copy, 0, strlen(first_word)-1);
            strcpy(symbol_name, substring_symbol_copy);
            if((current_error = valid_symbol(symbol_name, macro_table)) != Error_Success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }

            symbol_flag = 1;
            sscanf(line + offset, "%s%n", first_word, &after_label_offset);
            offset += after_label_offset;
        }

        /*DATA IMAGE SECTION*/
        if((strcmp(first_word, ".data") == 0)){
            if((current_error = valid_data(line + offset)) != Error_Success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }

            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);
            }
            encode_data(line + offset);
            continue;
        }
        else if(strcmp(first_word, ".string") == 0){
            if((current_error = valid_string(line + offset)) != Error_Success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }
            /*add string to datalist*/
            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);
            }
            encode_string(line + offset);
            continue;
        }
        /*ENTRY/EXTERN SECTION*/
        else if(strcmp(first_word, ".entry") == 0 || strcmp(first_word, ".extern") == 0) {
            content = init_entry_extern_context(first_word, line, offset, line_num, am_path);
            if(!handel_entry_extern(content, symbol_table, macro_table)) {
                free_entry_extern_context(content);
                error_found = 1;
                continue;
            }
            free_entry_extern_context(content);
            continue;
        }

        /*CODE SECTION*/
        if ((current_error = handel_opcode(line + offset, first_word, symbol_table, symbol_name, symbol_flag)) != Error_Success) {
            print_error(current_error, line_num, am_path);
            error_found = 1;
        }
    }
    /*DEBUG:*/
    print_symbol_table(symbol_table);
    fclose(am_file);
    if (first_word_copy != NULL) {
        free(first_word_copy);
        first_word_copy = NULL;
    }
    if (substring_symbol_copy != NULL) {
        free(substring_symbol_copy);
        substring_symbol_copy = NULL;
    }
    return error_found;

}



enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table) {
    Symbol new_symbol;
    new_symbol = (Symbol)handel_malloc(sizeof(struct symbol));

    if ((is_in_table(symbol_table, symbol_name) && new_symbol->count == 0)) return firstPassError_symbol_name_taken;

    if (type_flag == DATA_FLAG) {
        new_symbol->count = DC;
    }
    if (type_flag == OPCODE_FLAG) {
        new_symbol->count = IC+100;
    }
    if (type_flag == EXTERN_FLAG) {
        new_symbol->count = 0;
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


void print_symbol_table(hash_table table) {
    int i;
    Node current;

    printf("| %-11s | %-5s | %-6s |\n", "Symbol Name", "Count", "Flag");
    printf("|-------------|-------|-------|\n");

    for (i = 0; i < TABLE_SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            Symbol sym = (Symbol)current->value;
            printf("| " BOLD GREEN "%-11s" RESET " | " BOLD BLUE "%-5d" RESET " | " BOLD MAGENTA "%-6s" RESET " |\n",
                   current->key,
                   sym->count,
                   get_flag_name(sym->flag));
            current = current->next;
        }
    }
}

char* get_flag_name(enum symbol_flag flag) {
    switch (flag) {
        case DATA_FLAG:
            return "DATA";
        case OPCODE_FLAG:
            return "OPCODE";
        case EXTERN_FLAG:
            return "EXTERN";
        case ENTRY_FLAG_OPCODE:
            return "ENTRY_OPCODE";
        case ENTRY_FLAG_DATA:
            return "ENTRY_DATA";
        default:
            return "---";
    }
}


void print_array(short arr[], int size) {
    int i;
    char* binary_str;

    printf("-------------------------------\n");
    for (i = 0; i < size; i++) {
        binary_str = short_to_binary_string(arr[i]);
        printf(""BOLD""MAGENTA "%d:  %s" RESET "\n", i + 100, short_to_binary_string(arr[i]));
        free(binary_str);

    }
    printf("-------------------------------\n");
}