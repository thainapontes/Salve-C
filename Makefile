CC = gcc
CFLAGS = -Wall -Werror -g -I$(INCLUDE_DIR)

PROJ_NAME = salve-c

BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj
SRC_DIR     = src
INCLUDE_DIR = include

SRC_FILES = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(OBJ_FILES)
	@echo Creating $(BUILD_DIR)/$(PROJ_NAME)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJ_NAME) $(OBJ_FILES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(BUILD_DIR)/Salve-C
