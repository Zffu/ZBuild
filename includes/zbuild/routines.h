/**
 * Routine definitions
 */

#pragma once

#include <stdint.h>

typedef struct zbuild_routine_t {
	uint8_t type;
	char* name;

	unsigned int* successors;
	int successor_sz;
} routine_t;
