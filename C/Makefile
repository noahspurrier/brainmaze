# makefile for Program #5 CMP101  NOAH SPURRIER

brainmaze : main.o maze.o
	gcc main.o maze.o -lm -o brainmaze

main.o : main.c handy.h maze.h
	gcc -g -c -ansi -pedantic -Wall main.c

maze.o : maze.c maze.h handy.h
	gcc -g -c -ansi -pedantic -Wall maze.c

