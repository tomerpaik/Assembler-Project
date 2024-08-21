.entry MAIN
.extern FUNC

MAIN:   mov r2, r3
        prn r5
        jsr FUNC
        jmp DONE

macr CALCULATE
        add r2, r4
        sub r3, r6
        inc r1
        dec r7
endmacr

DONE:   stop
NUMS:   .data 5, 15, -25
TEXT:   .string "Assembler"

        CALCULATE
