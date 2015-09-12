CFLAGS = -std=c11 -Wpedantic -Wall -Werror -O3 -m32

all: bin/triangle

.PHONY: multibuild
multibuild: src/triangle.c
	./test/multibuild.py -v -o ./bin/triangle -c "src/triangle.c $(CFLAGS)"

.PHONY: multitest
multitest: 
	./test/multitest.py -v -d bin -t ./test/gen_triangle_tests.py -a 10

.PHONY: equilateral_test
equilateral_test: bin/triangle
	./test/equilateral_test.py

bin/triangle: src/triangle.c
	$(CC) src/triangle.c -o bin/triangle $(CFLAGS)

.PHONY: test
test: bin/triangle
	./test/gen_triangle_tests.py ./bin/triangle 10

.PHONY: clean
clean:
	$(RM) bin/triangle*
	$(RM) -r bin/triangle.dSYM
