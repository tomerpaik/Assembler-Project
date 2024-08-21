.extern 1LABEL
.extern
.extern roy
.extern mov
.extern .data
.extern LABEL

STR: .string "abcd"
.extern LABEL
.extern STR
.entry 1LABEL
.entry
.entry roy
.entry mov
.entry .data
.extern LABEL
.entry LABEL

STR: .string "abcd"
.entry LABEL
.entry STR
.extern LABEL

