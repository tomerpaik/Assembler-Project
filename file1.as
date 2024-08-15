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
LAO: .data 7, 9, +21
DATA1: .data 6, -9
      .data -100
.data 31, 56
.string
.string abcd"
.string "a*bcd
.string "a\nbcd"
STR:.string "a\0bcd"
.string "ab"cd"
or