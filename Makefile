# Makefile to build a static library using gcc

CC = gcc
CFLAGS = -std=c2x -O2 -Wall -fPIC -Iinclude

SRC_DIR = source
INC_DIR = include
OBJ_DIR = obj
LIB_NAME = libstring.a

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(LIB_NAME)

$(OBJ_DIR):
	mkdir -p $@

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Ensure the directory exists before compiling
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME)
