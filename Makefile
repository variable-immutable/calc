CC=gcc

CFLAGS=-Wall -g

NAME=calc

all: main

main: calc.o list.o stack.o
	$(CC) $(CFLAGS) list.o stack.o calc.o -o $(NAME)

calc.o: calc.c calc.h
	$(CC) $(CFLAGS) -c calc.c calc.h

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c list.h

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c stack.h


clean:
	rm -rf *.o *.gch $(NAME)
