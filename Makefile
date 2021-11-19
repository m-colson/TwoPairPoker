CC=gcc
CFLAGS=-Wall

build: src/*.c
	$(CC) $(CFLAGS) -o 'build/main.exe' 'src/main.c'

run: src/*.c
	$(CC) $(CFLAGS) -o 'build/main.exe' 'src/main.c'
	./build/main

test: tests/*.test.c
	$(CC) $(CFLAGS) -o test.exe handutils.test.c
	./test