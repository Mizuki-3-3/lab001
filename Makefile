CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
TEST_SRC = tests/*.c
LIB_SRC = src/vector.c src/vector_int.c src/vector_double.c
TARGET = test_

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_SRC) -o $(TARGET)

clean:
	if exist *.o del *.o
	if exist test_.exe del test_.exe
run: test_.exe
	cmd.exe /c start cmd.exe /k test_.exe
.PHONY: all clean