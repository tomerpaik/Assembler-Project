#include "first_pass.h"

int first_pass(char * am_path) {
    int error_code;
    int line_num;
    FILE * am_file;
    char line[MAX_LINE_LENGTH];
    char first_word[MAX_LINE_LENGTH];
    char line_copy[MAX_LINE_LENGTH];
    am_file = open_new_file(am_path, ".am", "r");
    line_num = 0;

    /* Initialize  symbol table */
    /*TODO: check first if there is a line with more than Max characters*/

    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num ++;
        if (strcmp(line, "\n") == 0 || is_comment(line)) { /*blank line*/
            continue;
        }
        get_first_word(line, first_word);

        if (strchr(line, '.')) { /*instructions*/
            strcpy(line_copy, line);
            if (strstr(line_copy, ".data") != NULL || strstr(line_copy, ".string") != NULL){
                if (legal_label(first_word, &error_code)) { /*lable*/
                    /*insert_table(sym_table, first_word, "");*/
                    /*insert_label(symbols, first_word, DC, 1);*/
                }
            }else if (strstr(line_copy, ".entry") || strstr(line_copy, ".extern")) {
                printf("extern/entry\n");
            }else {
                /*Illegal data line directive - must be .data or .string or .extern or . entry */
                error_code = ERROR_CODE_58;
            }


        }else { /*commands*/
            continue;
        }

    }

    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return 1;

}