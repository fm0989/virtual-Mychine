# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ilib -g -std=c11

# Source files directory
SRC_DIR = src

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# List of object files (generated from the source files)
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = Mychine

# Default rule to build the program
all: $(TARGET)

# Rule to link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up by removing object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets
.PHONY: all clean