all: scrub clean baser fuzzer jbuild

base: 
	src/baser.o 337337 1024

fuzz:
	src/fuzzer.o 337338 1024 1

cmp: v24 v22

v24:
	../coreutils/src/sha1sum ./fuzz.txt

v22:
	sha1sum ./fuzz.txt

jrun:
	java -cp src Jsha1sum 1024

jbuild:
	javac src/*.java

baser:
	/usr/bin/gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition src/baser.c -o src/baser.o

fuzzer: 
	/usr/bin/gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition src/fuzzer.c -o src/fuzzer.o

test:
	python ./tester.py ${ARGS}

scrub:
	rm -f *.txt

clean: scrub
	rm -f src/baser.o src/fuzzer.o src/*.class *~
