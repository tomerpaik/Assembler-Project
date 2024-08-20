#ifndef FINISH_ENCODE_H
#define FINISH_ENCODE_H

/**
 * @file finish_encode.h
 * @brief Final encoding functions for the assembly process.
 *
 * This file contains declarations of functions used in the final encoding phase
 * of the assembly process, including symbol encoding, decoding of opcodes, and
 * handling of external and entry files.
 */

#include "first_pass.h"
#include "second_pass.h"
#include "symbol_struct.h"
#include "encode.h"

/* Represents a decoded opcode word with its addressing modes */
typedef struct {
    int opcode;             /**< The opcode value */
    short source_addressing; /**< The addressing mode for the source operand */
    short dest_addressing;  /**< The addressing mode for the destination operand */
} DecodedWord;

/**
 * @brief Encodes a symbol's address and appends it to the code image.
 *
 * This function encodes the address of a symbol and appends the encoded value
 * to the code image. If the symbol is external, it appends the symbol to the
 * external file instead.
 *
 * @param symbol_table The hash table containing symbols.
 * @param symbol_name The name of the symbol to encode.
 * @param symbol_adress The base address to encode the symbol with.
 * @param filename The name of the assembly file being processed.
 */
void encode_symbol(hash_table symbol_table, char *symbol_name, int symbol_adress, char *filename);

/**
 * @brief Decodes the first word of an encoded opcode.
 *
 * This function extracts the opcode, source addressing mode, and destination addressing mode
 * from an encoded instruction word.
 *
 * @param encoded_word The encoded word to decode.
 * @return A `DecodedWord` struct containing the decoded information.
 */
DecodedWord decode_opcode_first_word(short encoded_word);

/**
 * @brief Appends a symbol's information to an external or entry file.
 *
 * This function writes the symbol name and its address or line number to the appropriate
 * file (either `.ext` for external symbols or `.ent` for entry symbols).
 *
 * @param filename The base name of the file (without extension).
 * @param ending The file extension to use (e.g., ".ext" or ".ent").
 * @param symbol_name The name of the symbol to write.
 * @param line_number The line number or address associated with the symbol.
 */
void append_to_ext_ent_file(char *filename, char * ending, char *symbol_name, int line_number);

/**
 * @brief Converts a 4-bit addressing mode back to its original 3-bit form.
 *
 * This function reverses the encoding of an addressing mode, converting it
 * from its 4-bit encoded form back to the original 3-bit value.
 *
 * @param mode The encoded 4-bit addressing mode.
 * @return The original 3-bit addressing mode.
 */
short reverse_convert_addressing_mode(short mode);

#endif /* FINISH_ENCODE_H */