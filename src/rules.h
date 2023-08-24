#ifndef RULES_H
#define RULES_H

#include "types.h"

/* ================================================================ */

/**
 * Generate the next generation of an elementary cellular automaton.
 * 
 * @param current the current generation
 * @param previous the previous generation. The one that is being used as an input to produce the current generation
 * @param size the size of array, generations
 * @param rule rule to apply
 * 
 * @return none. Upon return, `current` array contains the current generation of the automaton.
*/
void apply_2E_CA(unsigned char* current, unsigned char* previous, ssize_t size, unsigned char rule);

/* ================================================================ */

/**
 * Generate the next generation of a totalistic cellular automaton with 3 colors.
 * 
 * @param current the current generation
 * @param previous the previous generation. The one that is being used as an input to produce the current generation
 * @param size the size of array, generations
 * @param rule rule to apply. This is an array representing a ternary number
 * 
 * @return none. Upon return, `current` array contains the current generation of the automaton.
*/
void apply_3T_CA(unsigned char* current, unsigned char* previous, ssize_t size, const unsigned char* rule);

/* ================================================================ */

/**
 * Generate the next generation of an ordinary mobile automaton.
*/
void apply_MO_CA(unsigned char* current, unsigned char* previous, ssize_t size, ssize_t rule_1, ssize_t rule_2);

#endif /* RULES_H */