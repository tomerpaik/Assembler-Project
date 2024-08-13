#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "globals.h"
#include "errors_handle.h"
#include "general_functions.h"

/* Define the opcodes */
op_code OPCODES[] = {
        {"mov",  2, "0123", "123"},
        {"cmp",  2, "0123", "0123"},
        {"add",  2, "0123", "123"},
        {"sub",  2, "0123", "123"},
        {"lea",  2, "1", "123"},
        {"clr",  1, "", "123"},
        {"not",  1, "", "123"},
        {"inc",  1, "", "123"},
        {"dec",  1, "", "123"},
        {"jmp",  1, "", "12"},
        {"bne",  1, "", "12"},
        {"red",  1, "", "123"},
        {"prn",  1, "", "0123"},
        {"jsr",  1, "", "12"},
        {"rts",  0, "", ""},
        {"stop", 0, "", ""}
};
/* Define the registers */
char *REGS[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

/* Define the instructions */
char *INSTUCTIONS[] = {".data", ".string", ".extern", ".entry"};



int is_instr(char *str) {
    int i;

    /* Return 0 if the string is NULL */
    if (str == NULL) {
        return 0;
    }

    /* Iterate through the list of known instructions and compare the string with each instruction in the list */
    for (i = 0; i < INSTRUCTIONS_COUNT; i++) {
        if (strcmp(str, INSTUCTIONS[i]) == 0) {
            return 1; /* Return 1 if the string matches an instruction */
        }
    }
    return 0; /* Return 0 if the string is not a valid instruction */
}


int what_opcode(char *str) {
    int i;

    /* Return -1 if the string is NULL */
    if (str == NULL) {
        return -1;
    }

    /* Iterate through the list of known opcodes and compare the string with each opcode in the list */
    for (i = 0; i < OPCODES_COUNT; i++) {
        if (strcmp(str, OPCODES[i].opcode) == 0) {
            return i; /* Return the index of the matching opcode */
        }
    }
    return -1; /* Return -1 if the string does not match any known opcodes */
}


int what_reg(char *str) {
    int i;

    /* Return -1 if the string is NULL */
    if (str == NULL) {
        return -1;
    }

    /* Iterate through the list of known registers and compare the string with each register in the list */
    for (i = 0; i < REG_COUNT; i++) {
        if (strcmp(str, REGS[i]) == 0) {
            return i; /* Return the index of the matching register */
        }
    }
    return -1; /* Return -1 if the string does not match any known registers */
}

void get_first_word(char * line, char * first_word) {
    /* Allocate enough space for the first word */
    int offset = 0;
    sscanf(line, "%s%n", first_word, &offset);
}

int legal_label(char *str, int *error_code) {
    if (str == NULL) {
        return 0;
    }

    /* If str is in one of the following - the label name is not valid */
    if (strlen(str) > MAX_LABEL_LENGTH || !isalpha(*str) || what_reg(str) >= 0) {
        return 0;
    }

    if (what_opcode(str) < 0) {
        while (*(++str) != '\0' && (isalpha(*str) || isdigit(*str))) {;
        }
        if (*(str) == ':' && *(str + 1) == '\0') {
            *str = '\0';
            return 1;
        } else {
        }
    }

    return 0;
}

int is_comment(char * line) {
    return 0;
}





