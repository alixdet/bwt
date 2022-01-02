CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

bwt: bwt.c rotations.h rotations.c
	$(CC) $(CFLAGS) -o $@ $^

test: bwt test.sh
	./test.sh

clean:
	rm bwt

.PHONY: clean test
