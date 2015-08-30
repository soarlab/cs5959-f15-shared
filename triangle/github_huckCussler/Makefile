CC=/usr/bin/gcc
CFLAGS=-O2 -fmessage-length=0 -pedantic-errors -std=c99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -c

all: clean triangle

clean:
	rm -rf *.o triangle

triangle: triangle.o
	$(CC) triangle.o -o triangle -lm

triangle.o: triangle.c
	$(CC) $(CFLAGS) triangle.c