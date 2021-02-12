BIN=$(shell basename ${PWD})

${BIN}: ${BIN}.c
	gcc -pthread -o $@ $<

clean:
	rm *~

mrproper: clean
	rm ${BIN}

.PHONY: clean mrproper
