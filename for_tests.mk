CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
LDFLAGS = -L. -lvector -lm
TEST_SRC = tests/test_main.c tests/test_vector.c tests/assertions.c

all: test_.exe

test_.exe: $(TEST_SRC) libvector.a
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC) $(LDFLAGS)

clean:
	if exist *.o del *.o
	if exist test_.exe del test_.exe
	
run: test_.exe
	cmd.exe /c start cmd.exe /k test_.exe

rebuild: clean all run
.PHONY: all clean rebuild run