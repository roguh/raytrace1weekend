CC = gcc
CFLAGS = -std=c23 -Wall -Wpedantic -Oz -g -fsanitize=address
FAST_CFLAGS = -std=c23 -Wall -Wpedantic -O2
TCC_CFLAGS = -std=c23 -Wall -Wpedantic -Oz -g

TEST_DIR = c/tests/unit
SRC_DIR = c

# Find all test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS = $(TEST_SOURCES:.c=.bin)

# Find all main C files
MAIN_SOURCES = $(filter-out $(SRC_DIR)/vec3.c, $(wildcard $(SRC_DIR)/*.c))
MAIN_TARGETS = $(MAIN_SOURCES:.c=.bin)

# Default target
.PHONY: all clean test test-single fast-test view help tcc

all: test

# Compile individual test files
$(TEST_DIR)/%.bin: $(TEST_DIR)/%.c $(SRC_DIR)/vec3.c
	$(CC) $(CFLAGS) $< $(SRC_DIR)/vec3.c -o $@ -lm

# Compile main programs
$(SRC_DIR)/%.bin: $(SRC_DIR)/%.c $(SRC_DIR)/vec3.c
	$(CC) $(CFLAGS) $< $(SRC_DIR)/vec3.c -o $@ -lm

# Fast compilation (no sanitizers)
fast-test: CC = gcc
fast-test: CFLAGS = $(FAST_CFLAGS)
fast-test: $(TEST_TARGETS)

# TinyCC compilation
# TODO use my own compiler
tcc: CC = tcc
tcc: CFLAGS = $(TCC_CFLAGS)
tcc: $(TEST_TARGETS) $(MAIN_TARGETS)

# Run all tests
test:
	./c_test.sh

# Run single test
test-single:
	@if [ -z "$(FILE)" ]; then echo "Usage: make test-single FILE=vec3"; exit 1; fi
	make $(TEST_DIR)/$(FILE).bin
	./$(TEST_DIR)/$(FILE).bin

# View rendered images (replaces c_view.sh)
view:
	@if [ -z "$(FILE)" ]; then echo "Usage: make view FILE=listing1"; exit 1; fi
	$(MAKE) $(FILE).bin
	$(FILE).bin > $(FILE).ppm
	@if command -v magick >/dev/null; then magick $(FILE).ppm $(FILE).png; fi
	@if command -v magick >/dev/null; then magick $(FILE).ppm $(FILE).jpg; fi
	@if command -v open >/dev/null; then open $(FILE).png; fi

# Individual compilation like existing script
%.bin: %.c
	$(CC) $(CFLAGS) $< -o $@ -lm

# Standalone compilation (no vec3.c dependency)
$(SRC_DIR)/%.bin: $(SRC_DIR)/%.c
	@if grep -q "vec3" $<; then \
		$(CC) $(CFLAGS) $< $(SRC_DIR)/vec3.c -o $@ -lm; \
	else \
		$(CC) $(CFLAGS) $< -o $@ -lm; \
	fi

# Clean up (replaces clean.sh)
clean:
	find . -name "*.bin" -delete
	find . -name "*.ppm" -delete
	find . -name "*.png" -delete
	find . -name "*.o" -delete
	find . -name "*.tmp" -delete
	find . -name "*~" -delete
	@echo "🧹 Cleaned up all generated files"

# Help
help:
	@echo "Commands:"
	@echo "  make test                 - Run all tests"
	@echo "  make test-single FILE=vec3 - Run single test"
	@echo "  make view FILE=listing1    - Render image"
	@echo "  make clean                - Clean up"
