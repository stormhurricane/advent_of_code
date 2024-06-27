CC = gcc

CFLAGS = -I. -I../lib -Wall -g

SRC = main.c ../lib/line.c map.c
target = main

$(target): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	del /Q /S $(target).exe
