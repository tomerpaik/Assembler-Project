#include "first_pass.h"

int first_pass(char * am_path) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LINE_LENGTH];
    int error = 0;
    int symbol_flag = 0, offset = 0;
    am_file = open_new_file(am_path, ".am", "r");

    /* Initialize  symbol table */

    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        /*initial variables*/
        symbol_flag = 0;
        error = 0;

        sscanf(line, "%s%n", first_word, &offset);

        if(is_symbol(first_word, &error)) {
            if(error) {
                /* TODO: print_error(error); */
                continue;
            }
            strcpy(symbol_name, first_word);
            symbol_flag = 1;
            sscanf(line+offset, "%s", first_word);
        }
    }

    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return 1;

}

int is_symbol(const char *word, int *error) {
    int word_len = strlen(word);
    /*TODO: chek if word is a symbol*/
    if (word[word_len - 1] != ':') {
        return 0;
    }
    /*TODO: chek valid len*/
    if(word_len > 32){
        *error = 1;
    }
    /*TODO: check symbol start with a letter*/
    if (!isalpha(word[0])) {
        *error = 1;
    }
    /*TODO: chek if char in symbol is valid*/
    for (int i = 1; i < word_len - 1; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            *error = 1;
            return 0;
        }
    }



    return 1;
}