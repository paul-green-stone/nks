#include "rules.h"

/* ================================================================ */

void apply_2E_CA(unsigned char* current, unsigned char* previous, size_t size, unsigned char rule) {
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

void apply_3T_CA(unsigned char* current, unsigned char* previous, size_t size, const unsigned char* rule) {
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