CC = gcc
AR = ar

CFLAGS = -Wall -Wextra -Iinclude -std=c17

BUILD_DIR = build
SRC_DIR = src

LIB_NAME = libhttpserver.a
LIB = $(BUILD_DIR)/$(LIB_NAME)

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXAMPLE = example/main.c
EXAMPLE_BIN = $(BUILD_DIR)/example

all: $(LIB)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) rcs $@ $^

example: $(LIB)
	$(CC) $(CFLAGS) $(EXAMPLE) -L$(BUILD_DIR) -lhttpserver -o $(EXAMPLE_BIN)

run-example: example
	./$(EXAMPLE_BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean example run-example