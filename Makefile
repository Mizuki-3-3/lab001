CC = gcc
# #для компиляции тестов
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

#для сборки библиотеки
# CFLAGS = -Iinclude -Wall -Wextra -std=c11
# AR = ar
# ARFLAGS = rcs
# TARGET_LIB = libvector.a
# OBJS = vector.o vector_int.o vector_double.o

# all: $(TARGET_LIB)

# $(TARGET_LIB): $(OBJS)
# 	$(AR) $(ARFLAGS) $@ $^

# vector.o: src/vector.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# vector_int.o: src/vector_int.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# vector_double.o: src/vector_double.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	del $(OBJS) $(TARGET_LIB)

rebuild: clean all run
.PHONY: all clean rebuild run