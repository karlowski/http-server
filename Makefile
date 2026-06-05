CC = gcc
AR = ar

CFLAGS = -Wall -Wextra -Iinclude -std=c17
BUILD_DIR = build
SRC_DIR = src

LIB_NAME = libhttpserver.a
LIB = $(BUILD_DIR)/$(LIB_NAME)

SRCS = \
    $(SRC_DIR)/server/server.c \
    $(SRC_DIR)/router/router.c \
	$(SRC_DIR)/terminator/terminator.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXAMPLE = example/main.c
EXAMPLE_BIN = $(BUILD_DIR)/example

all: clean $(LIB)

clean:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/server $(BUILD_DIR)/router $(BUILD_DIR)/terminator

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

example: $(LIB)
	$(CC) $(CFLAGS) $(EXAMPLE) -L$(BUILD_DIR) -lhttpserver -o $(EXAMPLE_BIN)

run-example: example
	./$(EXAMPLE_BIN)

.PHONY: all clean example run-example