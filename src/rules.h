#ifndef RULES_H
#define RULES_H

#include <stdlib.h>
#include <sys/types.h>

/* ================================================================ */

void apply_CA_rule_N(unsigned char* current, unsigned char* previous, size_t size, unsigned char rule);

#endif /* RULES_H */