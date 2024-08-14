FLAGS := gcc -ansi -pedantic -Wall -g
OFLAGS = -c -o $@
CFILES := $(wildcard ./*.c)
OFILES := $(patsubst %.c, %.o, $(CFILES))

all: $(OFILES)
	$(FLAGS) $^ -o assembler

%.o: %.c %.h
	$(FLAGS) $< $(OFLAGS)

.PHONEY: clean val

clean:
	rm -rf *.o

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./assembler input
