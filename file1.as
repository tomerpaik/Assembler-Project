MAIN: add r3, LIST
LOOP: prn #48
macr    ordssdssssssssssssssssssssssssssssssssssss
 hello its me
endmacr
 lea STR, r6
 inc r6
 mov *r6, K
 sub r1, r4
 dec K
 jmp LOOP
player
END: stop
STR: .string "abcd"
LIST: .data 6, -9
      .data -100
K: .data 31
.string "abcd"
or