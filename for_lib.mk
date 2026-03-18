CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
OBJS = vector.o vector_int.o vector_double.o

all: libvector.a

libvector.a: $(OBJS)
	ar rcs $@ $^

vector.o: src/vector.c
	$(CC) $(CFLAGS) -c $< -o $@

vector_int.o: src/vector_int.c
	$(CC) $(CFLAGS) -c $< -o $@

vector_double.o: src/vector_double.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(OBJS) libvector.a

rebuild: clean all
.PHONY: all clean rebuild