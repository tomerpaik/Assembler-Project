.entry START
START:  mov r2, ,r3        ; Invalid: Extra comma
        add r1 r4          ; Invalid: Missing comma
        clr r1, r2         ; Invalid: Extra operand
END:    stop
        .string "Invalid String   ; Invalid: Missing closing quote
DATA1:  .data 5, ,12, 7     ; Invalid: Extra comma
DATA2:  .data               ; Invalid: Missing data
DATA3:  .data 5 7 9         ; Invalid: Missing commas
