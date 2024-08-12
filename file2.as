MAIN: add r3, LIST
LOOP: prn #48
macr  roy
 THIS IS  roy content

 roy is roy content
endmacr
macr  roy1 more_tet

endmacr
macr  roy2
 cmp r3, #-6
 bne END
endmacr
 lea STR, r6
 inc r6
 mov *r6, K
 sub r1, r4
 dec K
 jmp LOOP
END: stop
roy1
STR: .string "abcd"
roy2
LIST: .data 6, -9
      .data -100
K: .data 31
roy
