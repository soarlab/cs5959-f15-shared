all: clean triangle

triangle:
	/usr/bin/gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition triangle_analyzer.c -o triangle

test: clean triangle 
	python triangle_test.py

testv: clean triangle
	python triangle_test.py -v

clean:
	rm -f triangle
