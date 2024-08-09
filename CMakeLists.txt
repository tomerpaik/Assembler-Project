cmake_minimum_required(VERSION 3.28)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler pre_assembler.c
        pre_assembler.h
        linked_list.h
        linked_list.c
        hash_table.c
        hash_table.h
        first_pass.c
        first_pass.h
        main.c
        main.h
        general.h
        general.c
        errors.c
        errors.h
        lexer.c
        lexer.h
        globals.h
)
