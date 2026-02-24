#!/bin/bash

# Simple TUI test runner - uses makefile for compilation
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
BOLD='\033[1m'
NC='\033[0m'

clear
echo -e "${BOLD}${BLUE}🧪 Test Runner${NC}"
echo "=================="

TEST_DIR="c/tests/unit"
passed=0
failed=0
total=0

# Find test files
test_files=$(find "$TEST_DIR" -name "*.c" 2>/dev/null)

if [ -z "$test_files" ]; then
    echo -e "${RED}No tests found in $TEST_DIR${NC}"
    exit 1
fi

# Count total tests
for test_file in $test_files; do
    total=$((total + 1))
done

echo "Found $total test(s)"
echo ""

# Run each test
for test_file in $test_files; do
    test_name=$(basename "$test_file" .c)
    current=$((passed + failed + 1))

    # Progress bar
    printf "\r${BLUE}[%d/%d]${NC} Testing %s... " "$current" "$total" "$test_name"

    # Use makefile to compile
    if make "${test_file%.c}.bin"; then
        # Run the test
        if ./"${test_file%.c}.bin" >/dev/null 2>&1; then
            printf "${GREEN}✓${NC}\n"
            passed=$((passed + 1))
        else
            printf "${RED}✗ FAILED${NC}\n"
            failed=$((failed + 1))
        fi
    else
        printf "${RED}✗ BUILD FAILED${NC}\n"
        failed=$((failed + 1))
    fi
done

echo ""
echo "=================="

# Results
if [ $failed -eq 0 ]; then
    echo -e "${GREEN}${BOLD}🎉 All $passed tests passed!${NC}"
    exit 0
else
    echo -e "${RED}${BOLD}💥 $failed/$total tests failed${NC}"
    echo -e "${GREEN}✓ $passed passed${NC} ${RED}✗ $failed failed${NC}"
    exit 1
fi
