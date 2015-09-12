all: triangle 
clean: rm -f Program *.o
.PHONY: all clean

CFLAGS := -std=c99

triangle: triangle.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
triangle.o: triangle.c
