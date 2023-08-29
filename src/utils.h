#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/* ================================================================ */

/**
 * Converts a decimal number to a ternary (base 3) number
 * 
 * @param number the decimal number to be converted
 * 
 * @return the ternary representaion of the decimal number on success, NULL on failure
*/
extern unsigned char* d2B(size_t number, int base);

/* ================================================================ */

/**
 * Swap two arrays with the given size.
 * 
 * @param a array 1
 * @param b array 2
 * @param size the size of arrays
 * 
 * @return none. Upon return, array `a` contains all the elements of `b` array, `b` contains all the elements of `a`.
*/
extern void swap(char* a, char* b, size_t size);

/* ================================================================ */

/**
 * Print usage statement for the program.
*/
void print_usage_message(const char* caller_name);

/* ================================================================ */

/**
 * Display all the information about the automaton that is currently being explored
*/
void App_info(struct __application* app);

/* ================================================================ */

/**
 * Parse the .xml files containing a Turing machine states
*/
void parse_XML_states(const App* app, const char* filename);

/* ================================================================ */

#endif /* UTILS_H */