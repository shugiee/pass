# === Project configuration ===
TARGET := myproject
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

CC := gcc
CFLAGS := -Wall -Wextra -std=c17 -I$(INC_DIR)

# === Collect all source files ===
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# === Default target ===
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# === Compile each .c into .o ===
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Convenience targets ===
.PHONY: run clean

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

