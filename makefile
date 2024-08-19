FLAGS := gcc -ansi -pedantic -Wall -g
OFLAGS = -c -o $@
CFILES := $(wildcard SourceFiles/*.c)
OFILES := $(patsubst SourceFiles/%.c, %.o, $(CFILES))

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows
    DEL := del /Q
else
    # Unix-like (macOS, Linux)
    DEL := rm -f
endif

# Targets
all: $(OFILES)
	$(FLAGS) $^ -o assembler

%.o: SourceFiles/%.c Headers/%.h
	$(FLAGS) $< $(OFLAGS)

.PHONY: clean val

clean:
	$(DEL) *.o assembler

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./assembler file1