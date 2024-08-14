MAIN add r3, LIST
1OOP: prn #48
macr    or
 hello its me
endmacr
 lea STR, r6
 inc r6
 mov *r6, K
 sub r1, r4
 dec K
 jmp LOOP
player
E*ND: stop
stop: .string "abcd"
r7: .data 6, -9
      .data -100
or: .data 31
.string "abcd"
or