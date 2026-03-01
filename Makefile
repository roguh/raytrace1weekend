CC = tcc
CFLAGS:=-std=c23 -Wall -Wpedantic -O2 -g
# Address sanitizer for debugging null pointer derefs and memory safety
# Remove for TCC
# CFLAGS+=-fsanitize=address
# Exhaustive enums if no default
CFLAGS+=-Werror=switch
# -MMD generates Makefiles with file extension .d that contain the dependencies of each object
CFLAGS+=-MMD
LDLIBS:=-lm
LDFLAGS:=

MAINS:=$(wildcard c/*.c c/tests/unit/*.c)
LIBS=$(wildcard c/lib/*.c)
OBJS_LIB:=$(LIBS:.c=.o)
SRCS:=$(MAINS) $(LIBS)
DEPS:=$(SRCS:.c=.d)
PROGRAMS:=$(MAINS:.c=)

# Default target
.PHONY: all clean view help

all: test

test:
	./c_test.sh

# Dependency gathering with -MMD flag
-include $(DEPS)

# Generic binary building rule after -MMD configuration
%: %.c $(OBJS_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# View rendered images (replaces c_view.sh)
view:
	@if [ -z "$(FILE)" ]; then echo "Usage: make view FILE=listing1"; exit 1; fi
	$(MAKE) $(FILE)
	$(FILE) > $(FILE).ppm
	@if command -v magick >/dev/null; then magick $(FILE).ppm $(FILE).png; fi
	@if command -v magick >/dev/null; then magick $(FILE).ppm $(FILE).jpg; fi
	@if command -v open >/dev/null; then open $(FILE).png; fi

# Clean up (replaces clean.sh)
clean:
	rm -f $(PROGRAMS)
	find . -name "*.ppm" -delete
	find . -name "*.png" -delete
	find . -name "*.o" -delete
