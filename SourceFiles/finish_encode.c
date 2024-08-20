#include "../Headers/finish_encode.h"

#include <stdio.h>
#include <string.h>


void encode_symbol(hash_table symbol_table, char *symbol_name, int symbol_adress, char* file_name) {
    short encoded_word;
    short encoded_symbol_address;

    /* Calculate the symbol's address in memory, shifted and adjusted */
    encoded_symbol_address = (get_symbol_count(symbol_table, symbol_name)+ symbol_adress + 100) << 3;
    if (get_symbol_flag(symbol_table, symbol_name) == EXTERN_FLAG) {
        encoded_word = EXTERNAL;
        append_to_ext_ent_file(file_name, ".ext", symbol_name, IC+100);
    }else {
        encoded_word = encoded_symbol_address | RELOCATABLE;
    }
    append_to_code_image(encoded_word); /* without i++ in order to override current 0000... default value */
    IC++;
}

enum project_error handle_operand_symbol(char *operands, hash_table symbol_table, char * file_name) {
    DecodedWord decoded;
    char* source_operand;
    char* temp_dest;
    int label_save = IC;
    char* dest_operand = "NULL";
    int double_reg = 0;

    /* Decode the first word in the code image */
    decoded = decode_opcode_first_word(code_image[IC]);
    /* Extract and process the operands */
    source_operand = strtok(operands, ",");
    if (source_operand != NULL) {
        source_operand = str_without_spaces(source_operand);
        temp_dest = strtok(NULL, ",");
        if (temp_dest != NULL) {
            dest_operand = str_without_spaces(temp_dest);
        }
    }
    if (decoded.source_addressing == 4) {
        dest_operand = source_operand;

    }
    /* Skip the first word */

    IC++;

    /*Check if both operands are registers for double register encoding*/
    if ((decoded.source_addressing == 2 || decoded.source_addressing == 3) &&
        (decoded.dest_addressing == 2 || decoded.dest_addressing ==3)){/*Double Register Line*/
        double_reg = 1;
        IC++;
        decoded = decode_opcode_first_word(code_image[IC]);
    }
    if (!double_reg) {
        /* Handle source operand */
        if (decoded.source_addressing == 1) {
            if (!is_in_table(symbol_table, source_operand)) {
                return SECOND_PASS_ERROR_COMMAND_SYMBOL_OPERAND_NEXIST;
            }
            encode_symbol(symbol_table, source_operand, label_save, file_name);
            /*printf(""ORANGE"Encoded source operand: %s\n"RESET"", source_operand);*/
        } else if(decoded.source_addressing != 4) {
            IC++;
        }

        /* Handle destination operand */
        if (decoded.dest_addressing == 1) {
            if (!is_in_table(symbol_table, dest_operand)) {
                return SECOND_PASS_ERROR_COMMAND_SYMBOL_OPERAND_NEXIST;
            }
            encode_symbol(symbol_table, dest_operand, label_save, file_name);
            /*printf(""ORANGE"Encoded destination operand: %s\n"RESET, dest_operand);*/
        } else if(decoded.dest_addressing !=4){ /*dont skip a non method operand*/
            IC++;
        }
    }
    /* Free memory if allocated */
    return Error_Success;
}


DecodedWord decode_opcode_first_word(short encoded_word) {
    DecodedWord decoded;
    /*Extract opcode and addressing modes from the encoded word*/
    decoded.opcode = (encoded_word >> 11) & 0xF;   /* Extract the opcode (bits 12-15, 4 bits) */
    decoded.source_addressing = reverse_convert_addressing_mode((encoded_word >> 7) & 0xF);   /* Extract the source addressing mode (bits 8-11, 4 bits) */
    decoded.dest_addressing = reverse_convert_addressing_mode((encoded_word >> 3) & 0xF);     /* Extract the destination addressing mode (bits 4-7, 4 bits) */
    return decoded;
}

/* Function to convert a 4-bit addressing mode back to its original 3-bit form */
short reverse_convert_addressing_mode(short mode) {
    switch (mode) {
        case 1: return 0;  /* For encoding mode 0 (which is shifted to 1) */
        case 2: return 1;
        case 4: return 2;
        case 8: return 3;
        default: return 4; /* No method available */
    }
}

void append_to_ext_ent_file(char *filename, char * ending, char *symbol_name, int line_number) {
    FILE *file = open_new_file(filename, ending, "a");
    fprintf(file, "%-4s %04d\n", symbol_name, line_number);
    fclose(file);
}