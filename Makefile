# makefile for bmacs.
CC=gcc
WARNINGS=-Wall -Wstrict-prototypes
CFLAGS=-O2 $(WARNINGS) -g
LIBS=-lncurses
PROGRAM=bm

SRC=main.c screen.c

HDR=screen.h
HDRPATH=-I/usr/local/opt/ncurses/include

OBJ=screen.o main.o

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

clean:
	@rm -f $(PROGRAM) tags lintout *.o

tags: ${SRC}
	@rm -f tags
	ctags ${SRC}

lint: ${SRC}
	@rm -f lintout
	splint ${SRC} ${HDRPATH} > lintout
	cat lintout
