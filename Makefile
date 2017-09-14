CC=gcc
OUT=shell
SRC=shell.c command_shell.c
FLAGS=-Wall

all:
	$(CC) $(FLAGS) -o $(OUT) $(SRC)

install:
	cp $(OUT) /usr/local/bin/
