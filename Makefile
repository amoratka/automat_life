CFLAGS= -Wall 
all: life.out
life.out: main.o matrix.o block.o cellular_automaton.o draw.o
	$(CC) -o life.out main.o matrix.o block.o cellular_automaton.o draw.o -lalleg
main.o: main.c matrix.h draw.h cellular_automaton.h 
	$(CC) -c main.c matrix.c draw.c cellular_automaton.c
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c
block.o : block.c block.h matrix.h
	$(CC) $(CFLAGS) -c block.c
cellular_automaton.o : cellular_automaton.c cellular_automaton.h matrix.h block.h
	$(CC) $(CFLAGS) -c cellular_automaton.c
draw.o : draw.c draw.h matrix.h
	$(CC) $(CFLAGS) -c draw.c -lalleg
