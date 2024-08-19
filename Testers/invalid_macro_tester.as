MAIN: add r3, LIST
LOOP: prn #48
#Macro_ETA_MacroName
macr m_macr 09
 cmp r3, #-6
 bne END
endmacr
#Macro_nameis_Reg_Op_Inst
macr r1
 cmp r3, #-6
 bne END
endmacr
macr mov
 cmp r3, #-6
 bne END
endmacr
macr .data
 cmp r3, #-6
 bne END
endmacr
#Macro_namestart_with_numbers
macr 1m_macr
 cmp r3, #-6
 bne END
endmacr
#Macro_Without_Name
macr
 cmp r3, #-6
 bne END
endmacr
macr endmacr
 cmp r3, #-6
 bne END
endmacr
macr macr
 cmp r3, #-6
 bne END
endmacr
macr macr
 cmp r3, #-6
 bne END
endmacr
#Macro_nameis_oor
macr macrooooooooooooooooooooooooooooooooooooooooooooo
 cmp r3, #-6
 bne END
endmacr
macr valid-macro

 valid macro data

endmacr
 lea STR, r6
 inc r6
 mov *r6,K
 sub r1, r4
 m_macr "
 m_macr
 dec K
 jmp LOOP
 valid-macro
END: stop
STR: .string “abcd”
LIST: .data 6, -9
OP: cmd f po
 .data -100