#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "globals.h"
#include "errors.h"
#include "general_functions.h"

/* Define the opcodes */
op_code OPCODES[] = {
        {"mov",  2},
        {"cmp",  2},
        {"add",  2},
        {"sub",  2},
        {"not",  1},
        {"clr",  1},
        {"lea",  2},
        {"inc",  1},
        {"dec",  1},
        {"jmp",  1},
        {"bne",  1},
        {"red",  1},
        {"prn",  1},
        {"jsr",  1},
        {"rts",  0},
        {"stop", 0}
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



