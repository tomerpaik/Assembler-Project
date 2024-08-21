.entry START
.extern EXTERNAL_LABEL
START:  mov r2, r3
        add r1, EXTERNAL_LABEL
        sub #10, r4
        prn r5
        jsr EXTERNAL_LABEL
        clr r1
LOOP:   inc r2
        bne LOOP
        jmp END
        .entry LOOP
END:    stop
        .string "Hello, World!"
DATA1:  .data 5, -12, 7
DATA2:  .data 255
DATA3:  .data 0, 100, -50
