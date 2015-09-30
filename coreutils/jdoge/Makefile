#gcov:
	#../coreutils make CFLAGS="-fprofile-arcs -ftest-coverage"

#clang:
	#../coreutils/make CC=clang CFLAGS="-fsanitize=address"

test:
	python test.py

fuzz:	
	python fuzzer.py