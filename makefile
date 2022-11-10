build: main.c array.c
	gcc -Wall -Wextra -std=c11 main.c array.c -o array

.PHONY: main.c array.c
main.c array.c: array.h

.PHONY: clean
clean:
	rm ./array
