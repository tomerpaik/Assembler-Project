#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"


/* Define constants for encoding */

/* Define a struct to hold decoded opcode information */
typedef struct {
    int opcode;
    short source_addressing;
    short dest_addressing;
} DecodedWord;

/* Function declarations */
void encode_symbol(hash_table symbol_table, char *symbol_name);
DecodedWord decode_opcode_first_word(short encoded_word);
short reverse_convert_addressing_mode(short mode);
/* Include other necessary declarations if needed */

#endif /* SECOND_PASS_H */
