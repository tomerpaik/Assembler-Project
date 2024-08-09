#include "pre_assembler.h"
#include "general_functions.h"
#include "globals.h"
#include "lexer.h"


int pre_assembler(char * file_name) {
    FILE *as_file , *am_file;
    HashTable* macroTable;
    macroTable = create_hash_table(TABLE_SIZE);

    /*error handleing trouble opening the file*/
    as_file = open_new_file(file_name, ".as", "r");
    if (as_file == NULL) {
        return 0;
    }
    am_file = open_new_file(file_name, ".am", "w");

    if (process_macros(as_file, am_file, macroTable)) {
        free_hash_table(macroTable);
        return 1;
    }

    fclose(as_file);
    fclose(am_file);
    return 0;

}
int process_macros(FILE * inputFile, FILE * outputFile, HashTable* macroTable){
    /*Initialize Varibals*/
    char line[MAX_LINE_LENGTH];
    char macroName[MAX_MACRO_NAME_LENGTH];
    char macroBody[MAX_MACRO_BODY];
    int inMacroFlag = 0;
    int macroReplaced = 0;
    char *macroContent;

    /*check macro*/
    int macro_name_offset = 0;
    int macr_offset = 0;
    int is_endmacr_offset;

    /*replace macro*/
    char *line_copy;
    char *token;



    macroBody[0] = '\0';
    /*running on the file */
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        macr_offset = is_macr(line); /*checks if the first word is "macr" define*/
        if (macr_offset) {
            macro_name_offset = get_macro_name(line, macroName, macr_offset);
            if (macro_name_offset) {
                inMacroFlag = 1;
                if (is_additional_text_after_macro_name(line, macro_name_offset + macr_offset)) {
                    return 0;
                }
            }else { /*after_M_name_offset = 0 -> there is no macro name */
                return 0;
            }
        } else if (is_endmacr_offset = is_endmacr(line)) {
            if (is_macro_additional_after_endmacr(line, is_endmacr_offset)) {
                return 0;
            }
            inMacroFlag = 0;
            if (is_valid_macro_name(macroName)) {                   /*checks whether macro name is an instructuion register or opcode*/
                printf("Macro Name: %s\n", macroName);
                if(in_table(macroTable, macroName)) {
                    insert_table(macroTable, macroName, macroBody);
                }

            }else {
                return 0;
            }
        } else if (inMacroFlag) {                                   /*in macro flag when we recognized macr and not endmacr means we are in the macro content*/
            strcat(macroBody, line);                               /*copping line (one of macro content lines) into macroBody array */
        } else {                                                  /*regular line (not a macro content or define of a macro */
            line_copy = strdup(line);                            /*creating line to manipulate without damaging the source line */
            token = strtok(line_copy, " \t\n");            /*gets the content from the first line to the end allow us to grab the macro call(name)*/
            if (token && search_table(macroTable, token)) {    /*serching the macro name in the hash table*/
                macroContent = search_table(macroTable, token);
                fputs(macroContent, outputFile);              /*macro set in new file instead of macro call*/
                macroReplaced = 1;
            }
            if (!macroReplaced) { /*copy the regular line to the output file in case it was not a macro*/
                fputs(line, outputFile);
            }

            macroReplaced = 0; /*line was not a macro call so there was nothing to replace within macro */
            macroBody[0] = '\0';
            free(line_copy); /*freeing new alocated line*/
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 1;
}


int is_additional_text_after_macro_name(char *line, int total_offset) {
    /* Move the pointer to the character immediately after the macro name */
    line += total_offset;

    /* Skip any spaces or tabs after the macro name */
    while (*line != '\0' && (*line == ' ' || *line == '\t')) {
        line++;
    }

    /* If we encounter anything other than a newline or end of the string, there's additional text */
    if (*line != '\0' && *line != '\n') {
        print_internal_error(ERROR_CODE_10);
        return 1; /* Additional characters found */
    }

    return 0; /* No additional characters found */
}
int is_macro_additional_after_endmacr(char *line, int offset) {

    /* Move the pointer to the character immediately after "endmacr" */
    line += offset;

    /* Skip any spaces or tabs after "endmacr" */
    while (*line == ' ' || *line == '\t') {
        line++;
    }

    /* Check if there's no additional characters after "endmacr" */
    if (*line == '\0' || *line == '\n') {
        return 0; /* Valid "endmacr" with no additional text */
    }

    print_internal_error(ERROR_CODE_12);

    return 1; /* Additional characters found */
}
int is_valid_macro_name(char *name) {
    if(is_instr(name) || what_opcode(name) >= 0 || what_reg(name) >=0) {
        print_internal_error(ERROR_CODE_17); /*TODO: shoud be external print*/
        return 0;
    }
    return 1;
}
int is_macr(char *line) {
    char first_word[MAX_LINE_LENGTH]; /* Allocate enough space for the first word */
    int offset = 0;
    /* Extract the first word and calculate the offset */
    if (sscanf(line, "%s%n", first_word, &offset) != 1) {
        return 0; /* Return 0 if no word was found */
    }
    /* Check if the first word is "macr" */
    if (strncmp(first_word, MACRO_START, strlen(first_word)) == 0) {
        /* Now, extract the macro name */
        return offset; /* Return the total offset */
    }
    return 0; /* Not a valid macro definition */
}
int is_endmacr(char *line) {
    char first_word[MAX_LINE_LENGTH]; /* Allocate enough space for the first word */
    int offset = 0;
    if (sscanf(line, "%s%n", first_word, &offset) != 1) {
        return 0; /* Return 0 if no word was found */
    }
    if (strncmp(first_word, MACRO_END, strlen(MACRO_END)) == 0) {
        return offset;
    }
    return 0;

}

int get_macro_name(const char *line, char *macroName, int macr_offset) {
    int macro_name_offset = 0;
    sscanf(line+macr_offset, "%s%n", macroName, &macro_name_offset);
    if (sscanf(line+macr_offset, "%s%n", macroName, &macro_name_offset) != 1) {
        print_internal_error(ERROR_CODE_9);
        return 0; /* Return 0 if no word was found */
    }
    return macro_name_offset;
}

