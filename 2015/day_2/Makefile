# Define the compiler and the flags
CC = gcc
CFLAGS = -Wall -Wextra -I.

# Define the executable file name
TARGET = main

# Define the source files
SRCS = main.c line.c

# Default target: build the executable
all: $(TARGET)

# Rule to link the object files to create the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
