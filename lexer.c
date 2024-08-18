#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "globals.h"
#include "errors_handle.h"
#include "general_functions.h"

/* Define the opcodes */
op_code OPCODES[] = {                         /*0  1  2  3  N*/                  /*0  1  2  3  N*/
    {"mov",  2, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 0}},  /* source: 1,2,3  | destination: 0,1,2,3 */
    {"cmp",  2, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 0}},  /* source: 0,1,2,3 | destination: 0,1,2,3 */
    {"add",  2, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 0}},  /* source: 1,2,3  | destination: 0,1,2,3 */
    {"sub",  2, {0, 1, 1, 1, 0}, {1, 1, 1, 1, 0}},  /* source: 1,2,3  | destination: 0,1,2,3 */
    {"lea",  2, {0, 1, 1, 1, 0}, {0, 0, 0, 1, 0}},  /* source: 1,2,3  | destination: 1 */
    {"clr",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 1, 0}},  /* no source operand | destination: 1,2,3 */
    {"not",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 1, 0}},  /* no source operand | destination: 1,2,3 */
    {"inc",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 1, 0}},  /* no source operand | destination: 1,2,3 */
    {"dec",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 1, 0}},  /* no source operand | destination: 1,2,3 */
    {"jmp",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 0, 0}},  /* no source operand | destination: 1,2 */
    {"bne",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 0, 0}},  /* no source operand | destination: 1,2 */
    {"red",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 1, 0}},  /* no source operand | destination: 1,2,3 */
    {"prn",  1, {0, 0, 0, 0, 1}, {1, 1, 1, 1, 0}},  /* no source operand | destination: 0,1,2,3 */
    {"jsr",  1, {0, 0, 0, 0, 1}, {0, 1, 1, 0, 0}},  /* no source operand | destination: 1,2 */
    {"rts",  0, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}},  /* no source operand | no destination operand */
    {"stop", 0, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1}}   /* no source operand | no destination operand */
};

/* Define the registers */
char *REGS[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

/* Define the instructions */
char *INSTRUCTIONS[] = {".data", ".string", ".extern", ".entry"};

int opcode_num(char *str) {
    int i;

    /* Return -1 if the str is NULL */
    if (str == NULL) {
        return -1;
    }
    /*check if there is op matching to str*/
    for (i = 0; i < NUMBER_OF_OPCODES; i++) {
        if (strcmp(str, OPCODES[i].opcode) == 0) {
            return i; /* Return the index of the matching opcode */
        }
    }
    return -1; /* Return -1 if the string does not match any known opcodes */
}

/*check if str is instruction*/
int is_instruction(char *str) {
    int i;

    /* Return 0 if the string is NULL */
    if (str == NULL) {
        return 0;
    }

    /* Iterate through the list of known instructions and check if str is an instruction*/
    for (i = 0; i < INSTRUCTIONS_COUNT; i++) {
        if (strcmp(str, INSTRUCTIONS[i]) == 0) {
            return 1; /* Return 1 if the string matches an instruction */
        }
    }
    return 0; /* Return 0 if the string is not a valid instruction */
}

/*if str is a register returns the register number, if not returns: -1*/
int register_num(char *str) {
    int i;

    /* Return -1 if the string is NULL */
    if (str == NULL) {
        return -1;
    }

    /* Iterate through the list of known registers and compare the string with each register in the list */
    for (i = 0; i < NUMBER_OF_REG; i++) {
        if (strcmp(str, REGS[i]) == 0) {
            return i; /* Return the index of the matching register */
        }
    }
    return -1; /* Return -1 if the string does not match any known registers */
}
/*gets the first word in the line*/
int get_first_word(char * line, char * first_word) {
    /* Allocate enough space for the first word */
    int offset = 0;
    sscanf(line, "%s%n", first_word, &offset);
    return offset;
}

int is_comment(char * line) {
    return 0;
}

char* substring(char *source, int start, int end) {
    int length = strlen(source);
    char *substr = (char*)handel_malloc((end + 1) * sizeof(char));
    int i;

    if (start < 0 || start > length || end < 0) {
        return NULL;
    }

    if (substr == NULL) {
        return NULL;
    }

    for (i = 0; i < end && (start + i) < length; i++) {
        substr[i] = source[start + i];
    }

    substr[i] = '\0';
    return substr;
}

int is_valid_ascci(char c) {
    return (c >= 32 && c <= 126);
}

/**
 * is_empty_line - Checks if a line is empty or contains only whitespace characters.
 * @line: The string to check.
 *
 * Return: 1 if the line is empty or only contains whitespace, 0 otherwise.
 */
int is_empty_line(const char *line) {
    while (*line != '\0') {  /* Iterate over each character in the line */
        if (!isspace((unsigned char)*line)) {
            return 0;  /* Found a non-whitespace character */
        }
        line++;
    }
    return 1;  /* Line is empty or only contains whitespace */
}

char* str_without_spaces(char *string) {
    char *start_ptr = string;
    char *end_ptr = string + strlen(string) - 1;

    while (isspace(*start_ptr)) start_ptr++;
    while (end_ptr > start_ptr && isspace(*end_ptr)) end_ptr--;

    return substring(start_ptr, 0, end_ptr - start_ptr + 1);
}

int is_comment_empty_line(char * line) {
    if (is_empty_line(line) || *line == ';') { /*if line starts with ; OR if line is empty */
        return 1;
    }
    return 0;
}

/**
 * Function to find a character in a string.
 * @param str The string to search within.
 * @param ch The character to search for.
 * @return 1 if the character is found, 0 if not found.
 */
/* Function to find if an integer exists in an array */
int find_int_in_array(int *array, int length, int value) {
    int i;
    for (i = 0; i < length; i++) {
        if (array[i] == value) {
            return 1;
        }
    }
    return 0;
}

