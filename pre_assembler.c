#include "pre_assembler.h"

#include <ctype.h>

#include "general_functions.h"
#include "globals.h"
#include "lexer.h"

/*TODO: ERROR_CODE_4, ERROR_CODE_15
 *The Line is too long IMPORTANT
 */
int pre_assembler(char * file_name, hash_table macro_table) {
    FILE *as_file , *am_file;
    /*error handleing trouble opening the file*/
    as_file = open_new_file(file_name, ".as", "r");
    if (as_file == NULL) {
        return 0;
    }
    am_file = open_new_file(file_name, ".am", "w");

    if (process_macros(as_file, am_file, macro_table)) {
        free_table(macro_table);    /*free_macro_table(macroTable);*/
        return 1;
    }

    fclose(as_file);
    fclose(am_file);
    return 0;

}
int process_macros(FILE * inputFile, FILE * outputFile, hash_table macroTable){
    /*Initialize Varibals*/
    char line[MAX_LINE_LENGTH];
    char word[MAX_LINE_LENGTH];
    char macroName[MAX_MACRO_NAME_LENGTH];
    int inMacroFlag = 0;
    int line_num = 0;
    int total_body_length = 0;
    /*check macro*/
    int macro_name_offset = 0;
    int offset = 0;
    /*running on the file */
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        line_num++;
        printf("(Line Number) %d >>>>>>\n", line_num);
        if(!line_length_valid(line, line_num)) {
            continue;
        }
        if (sscanf(line, "%s%n", word, &offset)) { /*if no word was found sscanf will return 0 we wiil continue to the next line*/
            if (!strcmp(word, MACRO_START)) {
                inMacroFlag = 1;
                if (!sscanf(line + offset, "%s%n", macroName, &macro_name_offset)) { /*scanf returns 0 means no name was found*/
                    print_internal_error(ERROR_CODE_9);
                    return 0;
                }
                if (!is_empty_after_key(line + macro_name_offset + offset)) { /*more text after macro name*/
                    print_internal_error(ERROR_CODE_10);
                    return 0;
                }
                if (!is_valid_macro_name(macroName)) {
                    return 0;
                }
                printf("Macro Name: %s\n", macroName);
                if (search_table(macroTable, macroName) == 0) {
                    total_body_length = 0;
                    insert_table(macroTable, macroName, "");
                }else {
                    print_internal_error(ERROR_CODE_13);
                    return 0;
                }
            }
            else if (!strcmp(word, MACRO_END)) {
                inMacroFlag = 0;
                if (!is_empty_after_key(line + offset)) {
                    print_internal_error(ERROR_CODE_12);
                    return 0;
                }
            }
            else if (inMacroFlag){
                add_to_macro_body(macroTable, line, macroName, &total_body_length);
            }
            else if(search_table(macroTable, word)){ /*check if first word is macro call*/
                if (!is_empty_after_key(line + offset)) {
                    print_internal_error(ERROR_CODE_16);
                    return 0;
                }
                printf("Macro Name %s, Macro Body To Put: %s, Macro Body To Put Adress: %p\n",macroName, (char*)search_table(macroTable, macroName), search_table(macroTable, macroName));
                fputs((char*)search_table(macroTable, word), outputFile);
            }else {
                fputs(line, outputFile);
            }
        }
    }
    print_table(macroTable);
    fclose(inputFile);
    fclose(outputFile);
    return 1;
}

int is_valid_macro_name(char *name) {
    if(is_instr(name) || what_opcode(name) >= 0 || what_reg(name) >=0) {
        print_internal_error(ERROR_CODE_17); /*TODO: shoud be external print*/
        return 0;
    }
    if (!strcmp(name, MACRO_START)) {
        print_internal_error(ERROR_CODE_11);
        return 0;
    }
    return 1;
}
void add_to_macro_body(hash_table macro_table, char *line, char *macroName, int *macro_len) {
    char *macro_val = (char*)search_table(macro_table, macroName);
    printf("Macro Name %s, Macro Body Adress %p\n", macroName, macro_val);

    if (macro_val == NULL) {
        printf("Error: Macro value not found for key '%s'\n", macroName);
        return;
    }

    int new_len = strlen(macro_val) + strlen(line) + 1; /*null terminator*/
    char *new_macro_val = realloc(macro_val, new_len);
    if (new_macro_val == NULL) {
        printf("Error: Realloc failed\n");
        return;
    }

    strcat(new_macro_val, (const char *)my_strdup(line));
}
