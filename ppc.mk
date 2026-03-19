CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -I"C:/tools_for_pdcurses/PDCurses-3.9"
LDFLAGS = -L"C:/tools_for_pdcurses/PDCurses-3.9/wincon" -lpdcurses -lm -L. -lvector

all: vector.exe

vector.exe: main.o interface.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: src/main.c include/interface.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o

interface.o: src/interface.c include/interface.h
	$(CC) $(CFLAGS) -c src/interface.c -o interface.o

clean:
	del *.o
	del vector.exe
run: vector.exe
	cmd.exe /c start cmd.exe /k vector.exe
rebuild: clean all run
	
.PHONY: all clean run rebuild