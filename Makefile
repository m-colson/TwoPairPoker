CC=gcc
CFLAGS=-Wall

build: src/*.c
	$(CC) $(CFLAGS) -o 'build/main.exe' 'src/main.c'

run: src/*.c
	$(CC) $(CFLAGS) -o 'build/main.exe' 'src/main.c'
	./build/main

flow: flow_diagram/flow.dot
	dot -Tsvg flow_diagram/flow.dot -o flow_diagram/flow.svg

test: tests/*.test.c
	$(CC) $(CFLAGS) -o test.exe handutils.test.c
	./test