#ifndef RULES_H
#define RULES_H

#include "types.h"

/* ================================================================ */

void apply_2E_CA(unsigned char* current, unsigned char* previous, size_t size, unsigned char rule);

/* ================================================================ */

void apply_3T_CA(unsigned char* current, unsigned char* previous, size_t size, const unsigned char* rule);

#endif /* RULES_H */