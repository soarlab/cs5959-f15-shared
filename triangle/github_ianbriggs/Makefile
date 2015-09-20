CFLAGS = -std=c11 -Wpedantic -Wall -Werror -O3

all: bin/triangle

bin/triangle: src/triangle.c
	$(CC) src/triangle.c -o bin/triangle $(CFLAGS)

.PHONY: test
test: bin/triangle
	./test/gen_triangle_tests.py ./bin/triangle 10

.PHONY: clean
clean:
	$(RM) bin/triangle*
	$(RM) -r bin/triangle.dSYM
