CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -march=native -flto -funroll-loops -fomit-frame-pointer
LDFLAGS = 

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Create a list of executables based on the test files
TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_FILES))

all: $(EXECUTABLE) $(TEST_EXECUTABLES)

# Rule for creating executables from source files
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Rule for creating test executables
$(BUILD_DIR)/%: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(SRC_DIR) $< -o $@

# Run all tests
test: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		./$$test; \
	done

# List all test executables
list-tests: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		echo ./$$test; \
	done

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean list-tests
