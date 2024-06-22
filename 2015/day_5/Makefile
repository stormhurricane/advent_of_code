#Set compiler
CC = gcc

#CFLAGS
CFLAGS = -I../lib -I. -g -Wall

SOURCES = main.c ../lib/line.c
target = main

# The first target defined in the makefile is the one
# used when make is invoked with no argument. Given the definitions
# above, this Makefile file will build the one named TARGET and
# assume that it depends on all the named OBJECTS files.
$(target): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	rm -f $(target)