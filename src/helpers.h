#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

/* ================================================================ */

/**
 * Convert a decimal number into a ternary (base 3 number)
*/
extern unsigned char* d2t(size_t number);

/* ================================================================ */

extern void swap(char* a, char* b, size_t size);

/* ================================================================ */

void print_usage_message(const char* caller_name);

/* ================================================================ */

void App_info(struct __application* app);

#endif /* HELPERS_H */