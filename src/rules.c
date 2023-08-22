#include "rules.h"

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
void apply_2E_CA(unsigned char* current, unsigned char* previous, ssize_t size, unsigned char rule) {
    /* =========== VARIABLES ========== */

    /* Loop variable */
    ssize_t i = 0;

    /* Left cell of the previous generation */
    char left;

    /* Middle cell of the previous generation */
    char middle;

    /* Right cell of the previous generation */
    char right;

    /* New value of the cell in the current generation */
    char value;

    /* ================================ */



    for (; i < size; i++) {

        /* Compute a left cell */
        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];

        /* Compute a middle cell */
        middle = previous[i];

        /* Compute a right cell */
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        /* Value is used as an array index */
        value = 4 * left + 2 * middle + right;

        /* ================================ */

        current[i] = (rule >> value) & 1;
    }

    /* ================================ */

    return ;

}

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
void apply_3T_CA(unsigned char* current, unsigned char* previous, ssize_t size, const unsigned char* rule) {
    /* =========== VARIABLES ========== */

    ssize_t i = 0;

    unsigned char left, middle, right;

    unsigned char total = 0;

    /* ================================ */

    for (; i < size; i ++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        total = left + middle + right;

        current[i] = rule[total] - '0';
    }

    /* ================================ */

    return ;
}