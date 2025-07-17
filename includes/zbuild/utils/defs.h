#pragma once

#define buffer_def(type, name) \
	typedef struct name { \
		type##* arr; \
		unsigned int sz; \
	} name; \

buffer_def(char, charbuffer_t)