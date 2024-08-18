FLAGS := gcc -ansi -pedantic -Wall -g
OFLAGS = -c -o $@
CFILES := $(wildcard ./*.c)
OFILES := $(patsubst %.c, %.o, $(CFILES))

all: $(OFILES)
	$(FLAGS) $^ -o assembler

%.o: %.c %.h
	$(FLAGS) $< $(OFLAGS)

.PHONEY: clean val

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows
    DEL := del /Q
else
    # Unix-like (macOS, Linux)
    DEL := rm -f
endif

clean:
	$(DEL) *.o

# Debug using gdb
debug: $(EXEC)
	gdb $(EXEC)

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./assembler test
