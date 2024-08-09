#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_LINE_LENGTH 82
#define INPUT_EXTENSION ".as"
#define OUTPUT_EXTENSION ".am"
#define MACRO_START "macr"
#define MACRO_END "endmacr"
#define TABLE_SIZE 100
/*The File contain all the global values in the program*/

/* Maximum length of a label in command line  */
#define MAX_LABEL_LENGTH 31

/* Maximum length of a single command line  */

/* Default IC value */
#define IC_INIT_VALUE 100

/* arbitrary very big number for line length */
#define BIG_NUMBER_CONST 1000

#define OPCODES_COUNT 16

#define REG_COUNT 8

#define WORD_LEN 12

#define ARE_BITS 2

#define RELOCATABLE_VALUE 2

#define EXTERNAL_VALUE 1

#define INSTRUCTIONS_COUNT 4

#define SIX_BITS_MAX 63

#define SIX_BITS 6

#define NUM_SEXTETES 2

#define MAX_NUM ((1 << (WORD_LEN-1)) - 1)

#define MIN_NUM (-(1 << (WORD_LEN-1)))

#endif