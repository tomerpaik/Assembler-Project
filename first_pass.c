#include "first_pass.h"

int first_pass(char * am_path) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LINE_LENGTH];
    int error = 0;
    int symbol_flag = 0, offset = 0;
    int line_num = 0;
    am_file = open_new_file(am_path, ".am", "r");
    printf("start first\n");
    /* Initialize  symbol table */
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        /*printf("line number: %d line is: %s", line_num, line);*/
        /*initial variables*/
        symbol_flag = 0;
        error = 0;

        sscanf(line, "%s%n", first_word, &offset);

        printf("line: %d, first word: %s\n", line_num, first_word);
        if(is_symbol(first_word, &error)) {
            printf("found symbol\n");
        }
    }

    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return 1;

}

int is_symbol(char *word, int *error) {
    int word_len = strlen(word);
    char *symbol_name = substring(my_strdup(word), 0, word_len-1);

    int i;

    /*check if word is a symbol*/
    if (word[word_len - 1] != ':') {
        return 0;
    }
    /*check valid len*/
    if(word_len > 32){
        *error = 1;
        printf("Error: valid len\n");
    }
    /*check if symbol is a save word - instruction*/
    if(is_instruction(symbol_name)) {
        *error = 1;
        printf("Error: symbol is instruction\n");
    }
    /*check symbol start with a letter*/
    if (!isalpha(word[0])) {
        *error = 1;
        printf("Error: symbol not start with a letter\n");
    }
    /*check if char in symbol is valid*/
    for (i = 1; i < word_len - 1; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            *error = 1;
            printf("Error: char is not valid\n");
        }
    }
    /*check if symbol is a save word - opcode*/
    if(opcode_num(symbol_name)>=0) {
        *error = 1;
        printf("Error: symbol is opcode\n");
    }
    /*check if symbol is a save word - reguster*/
    if(register_num(symbol_name)>=0) {
        *error = 1;
        printf("Error: symbol is reguster\n");
    }
    return 1;
}