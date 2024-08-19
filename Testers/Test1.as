macr macro
sub #60, r2
add *r2, *r3
endmacr
macr variables
integer: .data 71,80
str: .string "hello"
.entry str, integer
endmacr
I: inc r3
J: dec *r5
macro
variables
.extern sum
cmp str, integer
prn sum
stop
