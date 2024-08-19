#ifndef ENCODE_H
#define ENCODE_H
#include <stdlib.h>
#include <string.h>
#include "general_functions.h"
#include "first_pass.h"
void encode_data(char* data_arguments);
void encode_string(char* string_argument);
/**
 * Encode the first word of an opcode.
 *
 * @param instruction The instruction name (e.g., "mov").
 * @param source_addressing The addressing mode of the source operand.
 * @param dest_addressing The addressing mode of the destination operand.
 * @return The encoded first word, or -1 if the instruction is not valid.
 */

void encode_opcode(char * opcode_name, char * source_operand, char * dest_operand, int source_addressing_method, int dest_addressing_method);
short encode_opcode_first_word(char * opcode_name, int source_addressing, int dest_addressing);
short encode_opcode_double_register(char * source_reg, char * dest_reg, int source_addressing_method, int dest_addressing_method);
short encode_opcode_register(char * reg, int source_flag);

short convert_addressing_mode(int mode);

/**
 * Appends an encoded short value to the global data_image array.
 * @param encoded_value The short value to append.
 * @return 0 if successful, or -1 if there is not enough space.
 */
int append_to_data_image(short encoded_value);
int append_to_code_image(short encoded_value);


#endif
