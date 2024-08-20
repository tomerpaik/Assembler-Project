#ifndef ENCODE_H
#define ENCODE_H

/**
 * @file encode.h
 * @brief Functions for encoding assembly data, strings, and opcodes.
 *
 * This file contains declarations of functions used for encoding data, strings,
 * and opcodes during the assembly process. The encoded values are stored in
 * global arrays representing the code and data images.
 */

#include <stdlib.h>
#include <string.h>
#include "general_functions.h"
#include "first_pass.h"

/**
 * @brief Encodes data arguments into binary format and stores them in the data image.
 *
 * This function processes a comma-separated list of data arguments, converts
 * each number to a 15-bit binary format, and appends the result to the data image.
 *
 * @param data_arguments The string containing the data arguments to encode.
 */
void encode_data(char* data_arguments);

/**
 * @brief Encodes a string into binary format and stores it in the data image.
 *
 * This function converts each character of a string into its ASCII value,
 * encodes it into binary, and appends it to the data image. It also appends
 * a null terminator at the end.
 *
 * @param string_argument The string to encode.
 */
void encode_string(char* string_argument);

/**
 * @brief Encodes an entire opcode, including its operands, into binary format.
 *
 * This function encodes the first word of the opcode and any operands,
 * and appends the encoded values to the code image.
 *
 * @param opcode_name The name of the opcode (e.g., "mov").
 * @param source_operand The source operand (if any).
 * @param dest_operand The destination operand (if any).
 * @param source_addressing_method The addressing method used for the source operand.
 * @param dest_addressing_method The addressing method used for the destination operand.
 */
void encode_opcode(char * opcode_name, char * source_operand, char * dest_operand, int source_addressing_method, int dest_addressing_method);

/**
 * @brief Encodes the first word of an opcode into binary format.
 *
 * This function encodes the opcode name and addressing methods into the first word
 * of the instruction, following the format of the assembly language.
 *
 * @param opcode_name The name of the opcode.
 * @param source_addressing The addressing method for the source operand.
 * @param dest_addressing The addressing method for the destination operand.
 * @return The encoded first word.
 */
short encode_opcode_first_word(char * opcode_name, int source_addressing, int dest_addressing);

/**
 * @brief Encodes a register operand when both source and destination are registers.
 *
 * This function handles the encoding of both source and destination registers
 * in a single instruction word.
 *
 * @param source_reg The source register operand.
 * @param dest_reg The destination register operand.
 * @param source_addressing_method The addressing method used for the source operand.
 * @param dest_addressing_method The addressing method used for the destination operand.
 * @return The encoded instruction word containing both register operands.
 */
short encode_opcode_double_register(char * source_reg, char * dest_reg, int source_addressing_method, int dest_addressing_method);

/**
 * @brief Encodes a single register operand into binary format.
 *
 * This function encodes a register operand, taking into account whether it is
 * a source or destination operand.
 *
 * @param reg The register to encode.
 * @param source_flag A flag indicating if the register is a source (1) or destination (0).
 * @return The encoded register value.
 */
short encode_opcode_register(char * reg, int source_flag);

/**
 * @brief Converts an addressing mode to its binary representation.
 *
 * This function converts the addressing mode (e.g., direct, indirect)
 * into its corresponding binary format.
 *
 * @param mode The addressing mode (0, 1, 2, or 3).
 * @return The binary representation of the addressing mode.
 */
short convert_addressing_mode(int mode);

/**
 * @brief Appends an encoded value to the data image.
 *
 * This function adds a binary-encoded value to the global data image array,
 * which represents the data section of the assembled program.
 *
 * @param encoded_value The binary-encoded value to append.
 * @return 0 if successful, or -1 if there is not enough space in the data image.
 */
int append_to_data_image(short encoded_value);

/**
 * @brief Appends an encoded value to the code image.
 *
 * This function adds a binary-encoded value to the global code image array,
 * which represents the instruction section of the assembled program.
 *
 * @param encoded_value The binary-encoded value to append.
 * @return 0 if successful, or -1 if there is not enough space in the code image.
 */
int append_to_code_image(short encoded_value);

#endif /* ENCODE_H */