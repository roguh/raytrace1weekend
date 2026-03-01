#ifndef __common_h
#define __common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_PRINT(...) fprintf(stderr, ##__VA_ARGS__)
#define RAND_D ((double)rand() / (double)RAND_MAX)

#endif
