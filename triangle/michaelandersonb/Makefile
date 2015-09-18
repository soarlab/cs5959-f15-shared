all: triangle 
clean: rm -f Program *.o
.PHONY: all clean

CFLAGS := -std=c99

triangle: triangle.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
triangle.o: triangle.c
#Borrowed from http://stackoverflow.com/questions/13328394/make-ignores-std-c99-flag-when-compiling-and-linking-a-c-program
