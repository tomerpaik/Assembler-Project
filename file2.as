MAIN: add r3, LIST
LOOP: prn #48

.extern LABEL
.extern 1LABEL
.extern r1
.extern roy
.extern mov
.extern .data

macr  roy
 THIS IS  roy content

 roy is roy content
endmacr
macr  roy1

endmacr
macr  macro1
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
LIST: .data 6, -9
      .data -100
K: .data 31
roy
macro1

.extern STR

