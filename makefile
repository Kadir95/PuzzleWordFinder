CC = gcc
CFLAGS = -std=c99

default:	puzzle

puzzle:		main.c tree.c linkedlist.c puzzle.c
		$(CC) $(CFLAGS) -o puzzle main.c tree.c linkedlist.c puzzle.c

clean:
		$(RM) puzzle *.o *~
