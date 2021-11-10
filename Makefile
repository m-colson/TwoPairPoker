CC=gcc
CFLAGS=-Wall

build: *.c
	$(CC) $(CFLAGS) -o main.exe main.c

test: *.test.c
	$(CC) $(CFLAGS) -o test.exe handutils.test.c
	./test