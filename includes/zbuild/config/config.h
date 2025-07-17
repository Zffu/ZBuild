#pragma once

#include <stdint.h>

#include <zbuild/utils/fastmap.h>

#define fastmap_valtype value_t*

typedef struct zbuild_config_t {
	char* display_name;
	fastmap_t* variables;
} build_config_t;

typedef struct zbuild_value_t {
	uint8_t type;
	size_t ptrdata_size;
	void* ptr;
} value_t;
