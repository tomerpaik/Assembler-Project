#include "encode.h"


void encode_data(char* data_arguments) {
    short data_encoded = 0;
    char *number_token;
    char *argument_copy;
    long num_value;
    argument_copy = my_strdup(data_arguments);
    number_token = strtok(argument_copy, ","); /* Use strtok to split the data_argument by commas */

    while (number_token != NULL) {
        num_value = strtol(number_token, NULL, 10);         /* Convert the number string to a long integer */
        data_encoded = convert_to_15bit_binary(num_value);         /* Use the convert_to_15bit_binary function to encode the number */

        append_to_data_image(data_encoded); /*Adds the new short to the data image array*/
        DC++; /*updates the data counter*/
        /*
        printf(""CYAN"number %s\ndata encoded: -------%s-------\n" RESET " ",number_token, data_short_is_binary);
        */
        number_token = strtok(NULL, ","); /* Get the next argument */
    }

    if (argument_copy != NULL) {
        free(argument_copy);
        argument_copy = NULL;
    }

}

void encode_string(char* string) {
    char *string_without_spaces, *string_arguments;
    short encoded_char;
    int i;

    string_without_spaces = str_without_spaces(string);
    string_arguments = substring(string_without_spaces, 1, strlen(string_without_spaces) - 2);

    for (i = 0; i < strlen(string_arguments); i++) {
        encoded_char = (short)string_arguments[i]; /* Convert character to its ASCII value */
        append_to_data_image(encoded_char); /* Add the ASCII value to the data image */
        DC++; /* Update the data counter */
        /*
        printf(""CYAN"Character: %c, Encoded ASCII: %s\n" RESET, string_arguments[i], short_to_binary_string(encoded_char));
    */
    }

    /* Add the null terminator '\0' at the end of the string */
    encoded_char = 0;
    DC++;
    append_to_data_image(encoded_char);
    /*
    printf(""CYAN"Null terminator added: Encoded ASCII: %s\n" RESET, short_to_binary_string(encoded_char));
    */

    if (string_arguments != NULL) {
        free(string_arguments);
        string_arguments = NULL;
    }
    if (string_without_spaces != NULL) {
        free(string_without_spaces);
        string_without_spaces = NULL;
    }
}


void encode_opcode(char *opcode_name, char *source_operand, char *dest_operand, int source_addressing_method, int dest_addressing_method) {
    short general_encoded_word; short source_encoded_word = 0; short dest_encoded_word = 0; int found_reg = 0;
    /* Encode and append the first word of the opcode */
    general_encoded_word = encode_opcode_first_word(opcode_name, source_addressing_method, dest_addressing_method);
    append_to_code_image(general_encoded_word | ABSOLUTE);

    /*printf(""YELLOW"source_operand: %s\n"RESET"", source_operand);
    printf(""YELLOW"dest_operand: %s\n"RESET"", dest_operand);
    printf(""YELLOW"source_addressing_method: %d\n"RESET"", source_addressing_method);
    printf(""YELLOW"dest_addressing_method: %d\n"RESET"", dest_addressing_method);*/

    /* Handle source operand encoding */
    if (source_addressing_method != 4) {
        switch (source_addressing_method) {
            case 0: /* Immediate addressing */
                source_encoded_word = atoi(source_operand + 1) << 3; /*skip (#)*/
                break;
            case 1: /* Direct addressing */
                source_encoded_word = 0; /* Handle with appropriate label later */
                break;
            case 2: /* Register direct addressing */
                found_reg = 1;
                source_encoded_word = encode_opcode_register(source_operand + 1, 1);
                break;
            case 3: /* Register indirect addressing */
                found_reg = 1;
                source_encoded_word = encode_opcode_register(source_operand, 1); /* Skip the (*) symbol */
                break;
            default:
                printf("Error: Invalid source addressing method\n");
                return;
        }
        IC++;
        append_to_code_image(source_encoded_word | ABSOLUTE);
    }

    /* Handle destination operand encoding */
    if (dest_addressing_method != 4) {
        if (!found_reg || !(dest_addressing_method == 2 || dest_addressing_method == 3)) {
            switch (dest_addressing_method) {
                case 0: /* Immediate addressing */
                    dest_encoded_word = atoi(dest_operand + 1) << 3;
                    break;
                case 1: /* Direct addressing */
                    dest_encoded_word = 0; /* Handle with appropriate label later */
                    break;
                case 2: /* Register direct addressing */
                    dest_encoded_word = encode_opcode_register(dest_operand + 1, 0);
                    break;
                case 3: /* Register indirect addressing */
                    dest_encoded_word = encode_opcode_register(dest_operand, 0); /* Skip the (*) symbol */
                    break;
                default:
                    printf("Error: Invalid destination addressing method\n");
                    return;
            }
            IC++;
            append_to_code_image(dest_encoded_word | ABSOLUTE);
        } else {
            IC--; /* Adjust IC if double register addressing */
            dest_encoded_word = encode_opcode_double_register(source_operand, dest_operand, source_addressing_method,dest_addressing_method);
            append_to_code_image(dest_encoded_word | ABSOLUTE);
        }
    }
    IC++;
}

short encode_opcode_first_word(char * opcode_name, int source_addressing, int dest_addressing) {
    int i;
    short encoded_word; short name_encoded; short source_addressing_method_encoded; short dest_addressing_method_encoded;
    short opcode_number = -1;
    for (i = 0; i < NUMBER_OF_OPCODES; i++) {
        if (strcmp(OPCODES[i].opcode, opcode_name) == 0) {
            opcode_number = i;
            break;
        }
    }
    /* Encode the first word:
     * Bits 0-3: Opcode
     * Bits 4-5: Source addressing mode
     * Bits 6-7: Destination addressing mode
     */
    /*
    printf(""CYAN"OPCODE %s\n"RESET"", short_to_binary_string(opcode_number));
    */
    name_encoded = opcode_number << 11;
    source_addressing_method_encoded = (convert_addressing_mode(source_addressing) << 7);
    dest_addressing_method_encoded = (convert_addressing_mode(dest_addressing) << 3);
    if (source_addressing == 4) { /*no method availaible*/
        source_addressing_method_encoded = 0;
    }
    if (dest_addressing == 4) { /*no method availaible*/
        dest_addressing_method_encoded = 0; /*set method to be 0*/
    }
    encoded_word = name_encoded|source_addressing_method_encoded|dest_addressing_method_encoded;
    return encoded_word;
}
short encode_opcode_register(char * reg, int source_flag) {
    short encoded_word = 0;
    short register_number = register_num(reg);
    if (source_flag) {
         encoded_word = register_number << 6;
         return encoded_word;
    }
    encoded_word = register_number << 3;
    return encoded_word;
}
short encode_opcode_double_register(char * source_reg, char * dest_reg, int source_addressing_method, int dest_addressing_method) {
    short encoded_word;
    short source_register_number;
    short dest_register_number;

    if (source_addressing_method == 2) {
        source_reg += 1; /*skip (*)*/
    }
    if (dest_addressing_method == 2) {
        dest_reg += 1; /*skip (*)*/
    }
    source_register_number = register_num(source_reg);
    dest_register_number = register_num(dest_reg);
    encoded_word = source_register_number << 5 | dest_register_number << 2;
    return encoded_word;
}

/**
 * Converts an addressing mode to its binary representation.
 * @param mode: The addressing mode (0, 1, 2, or 3).
 * @return: The binary representation as a short integer.
 */
short convert_addressing_mode(int mode) {
    return (1 << mode);
}



int append_to_data_image(short encoded_value) {
    if (IC + DC >= MAX_MEMORY_SPACE-100) {
        return -1;
    }
    data_image[DC] = encoded_value;
    return 0;
}


int append_to_code_image(short encoded_value) {
    if (IC + DC >= MAX_MEMORY_SPACE-100) {
        return -1;
    }
    code_image[IC] = encoded_value;
    return 0;
}
