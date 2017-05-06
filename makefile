CC=g++
CFLAGS=-I.

ggraph: main.o ggraph.o
	$(CC) -o ggraph main.o ggraph.o -I.