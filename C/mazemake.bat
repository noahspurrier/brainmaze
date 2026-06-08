REM #makefile for Program #5 CMP101  NOAH SPURRIER
REM a.out : main.o maze.o
REM    gcc main.o maze.o -lm
REM
REM main.o : main.c handy.h maze.h
REM     gcc -g -c -ansi -pedantic -Wall main.c
REM
REM maze.o : maze.c maze.h handy.h
REM     gcc -g -c -ansi -pedantic -Wall maze.c
REM Unix makefile is above, DOS makefile is below. HA HA

cl /c maze.c
cl /c main.c
link maze+main,maze.exe;

