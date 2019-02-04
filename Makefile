# Makefile for todolist


# Directories
DIR_INC    = ./include
DIR_SRC    = ./src
DIR_OBJ    = ./obj
DIR_BIN    = ./bin

# Programs, etc.
CC       = gcc
CFLAGS   = -O2 -Wall -I ${DIR_INC}
PREFIX   = /usr/local
FILE_H     = todolist.h print_list.h getopt.h

# This program
SRC        = $(wildcard $(DIR_SRC)/*.c)

OBJ        = $(patsubst %.c, $(DIR_OBJ)/%.o, $(notdir ${SRC}))

.PHONY: clean install uninstall 

all: clean todolist

clean:
	rm -f $(DIR_OBJ)/*.o

todolist: ${OBJ}
	$(CC) -o $@ ${OBJ}

${DIR_OBJ}/todolist.o: ${DIR_OBJ}/print_list.o ${DIR_OBJ}/getopt.o ${DIR_OBJ}/print_list.o ${DIR_OBJ}/write_list.o

${DIR_OBJ}/print_list.o: ${DIR_OBJ}/read_list.o

${DIR_OBJ}/write_list.o: ${DIR_OBJ}/read_list.o

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: todolist
	mkdir ~/.todolist
	touch ~/.todolist/list.txt
	touch ~/.todolist/list_history.txt
	chmod 777 ~/.todolist/list.txt ~/.todolist/list_history.txt
	cp ./sentences-config ~/.todolist/sentences-config
	install -m 0755 todolist $(PREFIX)/bin

uninstall: 
	rm -r ~/.todolist
	rm ./obj/*.o
	rm $(PREFIX)/bin/todolist
