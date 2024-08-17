.entry LIST
.entry fn2
.extern fn1

macr m_macr
 cmp r3, #-6
 bne END
endmacr
macr m
 cmp r3, #-6
 bne END
endmacr

MAIN: add r3, LIST
jsr fn1
LOOP: prn #48
 lea STR, r6
 inc r6
 mov *r6, L3
 sub r1, r4
 cmp r3, #-6
 bne END
 add r7, *r6
         clr K
         sub L3, L3
        .entry MAIN
 jmp LOOP
 m_macr
 m
        END: stop
        STR: .string "abcd"
        LIST: .data 6, -9
         .data -100
        K: .data 31
        .extern fn1
        .entry fn1


