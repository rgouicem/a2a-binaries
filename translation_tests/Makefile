CC=gcc
CFALGS=-O0

all: add

%.o: %.c
	${CC} -c ${CFLAGS} $<

add: add.o
	${CC} -o $@ $<

clean:
	rm *~

mrproper: clean
	rm *.o

.PHONY: clean mrproper
