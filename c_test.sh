#!/bin/bash
# Simple TUI test runner - uses makefile for compilation

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
BOLD='\033[1m'
NC='\033[0m'

echo -e "${BOLD}${BLUE}🧪 Test Runner${NC}"
echo "=================="

TEST_DIR="c/tests/unit"
passed=0
failed=0
total=0

# Find test files
test_files=$(find "$TEST_DIR" -name "*.c" 2>/dev/null)

for test_file in $test_files; do
    total=$((total + 1))
done

echo "Found $total test(s)"

# Run each test
for test_file in $test_files; do
    test_name=$(basename "$test_file" .c)
    current=$((passed + failed + 1))

    printf "\r${BLUE}[%d/%d]${NC} Testing %s... " "$current" "$total" "$test_name"

    if make "${test_file%.c}"; then
        if ./"${test_file%.c}" >/dev/null 2>&1; then
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

echo "=================="

echo -e "${GREEN}✓ $passed passed${NC} ${RED}✗ $failed failed${NC}"
if [ $failed -gt 0 ]; then
    echo -e "${RED}${BOLD}💥 $failed/$total tests failed${NC}"
    exit 1
fi
