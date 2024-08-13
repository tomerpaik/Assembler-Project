#include "pre_assembler.h"
int pre_assembler(char * file_name, hash_table macro_table) {
    FILE *as_file , *am_file;
    /*error handleing trouble opening the file*/
    as_file = open_new_file(file_name, ".as", "r");
    if (as_file == NULL) {
        return 0;
    }
    am_file = open_new_file(file_name, ".am", "w");

    if (process_macros(as_file, am_file, file_name, macro_table)) {
        free_table(macro_table);    /*free_macro_table(macroTable);*/
        return 1;
    }
    fclose(as_file);
    fclose(am_file);
    return 0;
}
int process_macros(FILE * inputFile, FILE * outputFile,char * file_name, hash_table macroTable){
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
        memset(word, 0, sizeof(word)); /*reset word TODO:*/
        line_num++;
        /*
        printf("---------- LINE: %d ------- %s", line_num, line);
        */
        if(!line_length_valid(line, line_num)) {
            printf("line number %d is out of range\n", line_num);
            continue;
        }
        /*TODO: if no word was found sscanf will return 0 we wiil continue to the next line*/
        sscanf(line, "%s%n", word, &offset);
        if (!strcmp(word, MACRO_START)) {
            inMacroFlag = 1;
            if (!sscanf(line + offset, "%s%n", macroName, &macro_name_offset)) { /*scanf returns 0 means no name was found*/
                print_error(Macro_Without_Name, line_num, file_name);
                return 0;
            }
            if (!is_empty_after_key(line + macro_name_offset + offset)) { /*more text after macro name*/
                print_error(Macro_ETA_MacroName, line_num, file_name);
                return 0;
            }
            if (!is_valid_macro_name(macroName, line_num, file_name)) {
                return 0;
            }
            if (search_table(macroTable, macroName) == 0) {
                total_body_length = 0;
                insert_table(macroTable, macroName, "");
            }else {
                print_error(Macro_double_define, line_num, file_name );
                return 0;
            }
        }
        else if (!strcmp(word, MACRO_END)) {
            inMacroFlag = 0;
            if (!is_empty_after_key(line + offset)) {
                print_error(Macro_ETA_endmacr, line_num, file_name);
                return 0;
            }
        }
        else if (inMacroFlag){
            add_to_macro_body(macroTable, line, macroName, &total_body_length);
        }
        else if(search_table(macroTable, word)){ /*check if first word is macro call*/
            if (!is_empty_after_key(line + offset)) {
                print_error(Macro_ETA_MacroCall, line_num, file_name);
                return 0;
            }
            fputs((char*)search_table(macroTable, word), outputFile);
        }else {
            fputs(line, outputFile);
        }

    }
    return 1;
}
int is_valid_macro_name(char *name, int line_num, char * file_name) {
    if(is_instr(name) || what_opcode(name) >= 0 || what_reg(name) >=0) {
        print_error(Macro_nameis_Reg_Op_Inst, line_num, file_name); /*TODO: shoud be external print*/
        return 0;
    }
    if (!strcmp(name, MACRO_START)) {
        print_error(macro_name_MACR, line_num, file_name);
        return 0;
    }
    return 1;
}
void add_to_macro_body(hash_table table, char *line, char *macroName, int *macro_len) {
    char *macro_val = (char*)search_table(table, macroName);
    int new_len = *macro_len + strlen(line) + 1;
    char *after_realloc_body = realloc(macro_val, new_len);
    if (after_realloc_body == NULL) {
        printf("Error: Realloc failed\n");
        return;
    }

    strcat(after_realloc_body, line);
    set_body_value(table, macroName, after_realloc_body);
    *macro_len = new_len;
}
void set_body_value(hash_table table, char *macroName, char *new_macro_val) {
    unsigned int index = hash(macroName);
    Node node = table[index];
    while (node != NULL) {
        if (strcmp(node->key, macroName) == 0) {
            node->value = new_macro_val;
            break;
        }
        node = node->next;
    }
}
