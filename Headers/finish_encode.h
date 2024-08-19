#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "first_pass.h"
#include "second_pass.h"
#include "symbol_struct.h"
#include "encode.h"

/* Define constants for encoding */

/* Define a struct to hold decoded opcode information */
typedef struct {
    int opcode;
    short source_addressing;
    short dest_addressing;
} DecodedWord;

/* Function declarations */
void encode_symbol(hash_table symbol_table, char *symbol_name, int symbol_adress, char *filename);
DecodedWord decode_opcode_first_word(short encoded_word);
void append_to_ext_ent_file(char *filename, char * ending, char *symbol_name, int line_number);
short reverse_convert_addressing_mode(short mode);
/* Include other necessary declarations if needed */

#endif /* SECOND_PASS_H */
