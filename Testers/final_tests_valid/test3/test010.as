.extern EXTERN_LABEL
.entry ENTRY_LABEL
        .data 1, 2, 3, -4
        .string "Complex Test"
        mov r1, EXTERN_LABEL
        add r2, ENTRY_LABEL
        jsr EXTERN_LABEL
        prn r4
ENTRY_LABEL: stop
MEMORY_TEST: .data 1000