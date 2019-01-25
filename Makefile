# Makefile for todolist

# Programs, etc.
CC       = gcc
PREFIX   = /usr/local

# This program
DIR_SRC    = ./src
DIR_BIN    = ./bin

FILE_H     = todolist.h
FILE_C     = todolist.c

FILE_O     = todolist.o

BIN_TARGET = $(DIR_BIN)/$(FILE_O)

.PHONY: clean everything all install uninstall 

clean :
	rm -f *.o

everything: $(BIN_TARGET)

all: clean everything

todolist: $(DIR_SRC)/todolist.c $(DIR_SRC)/todolist.h
	$(CC) -o $@ $<

install: todolist
	install -m 0755 todolist $(PREFIX)/bin

uninstall: 
	rm $(PREFIX)/bin/todolist
