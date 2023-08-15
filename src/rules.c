#include "rules.h"

/* ================================================================ */

void apply_CA_rule_N(unsigned char* current, unsigned char* previous, size_t size, unsigned char rule) {
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