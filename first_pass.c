#include "first_pass.h"
#include "errors.h"
#include "lexer.h"
#include "macro_table.h"
#include "symbole_table.h"

int  first_pass(char * am_path) {
    int error_code, IC, DC, error_found, label_table_line, externs_count, entries_count, inst_created = 1;
    DC = 0;
    int lable_flag = 0;
    int line_num = 0;
    FILE * am_file;
    char first_word[MAX_LINE_LENGTH];
    char line_copy[MAX_LINE_LENGTH];
    symbol_table * symbol_table;
    symbol_table = create_symbol_table(TABLE_SIZE);

    am_file = open_new_file(am_path, ".am", "r");

    char line[MAX_LINE_LENGTH];
    IC = 100;  /* Assuming starting address is 100 */

    /* Initialize your symbol table */
    Macro_Table* sym_table;
    sym_table = create_macro_table(TABLE_SIZE);

    /*TODO: check first if there is a line with more than Max characters*/

    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num ++;
        if (strcmp(line, "\n") == 0 || is_comment(line)) { /*blank line*/
            continue;
        }
        /* Remove any leading/trailing whitespace */
        get_first_word(line, first_word);


        if (strchr(line, '.')) { /*instructions*/
            strcpy(line_copy, line);
            if (strstr(line_copy, ".data") != NULL || strstr(line_copy, ".string") != NULL){
                if (legal_label(first_word, &error_code)) { /*lable*/
                    /*insert_table(sym_table, first_word, "");*/
                    insert_label(symbol_table, first_word, DC, 1);
                }
            }else if (strstr(line_copy, ".entry") || strstr(line_copy, ".extern")) {
                printf("extern/entry\n");
            }else {
                /*Illegal data line directive - must be .data or .string or .extern or . entry */
                inst_created = 0;
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
