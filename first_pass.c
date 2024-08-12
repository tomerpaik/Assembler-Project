#include "first_pass.h"
int first_pass(char * am_path) {
    int error_code;
    int line_num;
    FILE * am_file;
    char line[MAX_LINE_LENGTH];
    am_file = open_new_file(am_path, ".am", "r");
    line_num = 0;

    /* Initialize  symbol table */
    /*TODO: check first if there is a line with more than Max characters*/

    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        /*if(bool is_valid_line(line, tokenized_line)) {
            encode(tokenized_line);
        }*/
    }

    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return 1;

}