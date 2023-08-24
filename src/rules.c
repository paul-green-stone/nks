#include "rules.h"

/* ================================================================ */

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
    char total;

    /* ================================ */



    for (; i < size; i++) {

        /* Compute a left cell */
        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];

        /* Compute a middle cell */
        middle = previous[i];

        /* Compute a right cell */
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        /* Value is used as an array index */
        total = 4 * left + 2 * middle + right;

        /* ================================ */

        current[i] = (rule >> total) & 1;
    }

    /* ================================ */

    return ;

}

/* ================================================================ */

void apply_3T_CA(unsigned char* current, unsigned char* previous, ssize_t size, const unsigned char* rule) {
    /* =========== VARIABLES ========== */

    ssize_t i = 0;

    unsigned char left, middle, right;

    unsigned char total = 0;

    /* ================================ */

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        total = left + middle + right;

        current[i] = rule[total] - '0';
    }

    /* ================================ */

    return ;
}

/* ================================================================ */

void apply_MO_CA(unsigned char* current, unsigned char* previous, ssize_t size, ssize_t rule_1, ssize_t rule_2) {
    /* =========== VARIABLES ========== */

    /**
     * 2 corresponds to an active cell with white color (2 = 2 + 0)
     * 3 corresponds to an active cell with black color (3 = 2 + 1) 
    */

    ssize_t i = 0;

    unsigned char left, middle, right;

    unsigned char total = 0;

    /* ================================ */

    for (; i < size; i++) {

        if (previous[i] > 1) {

            left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
            middle = previous[i] - 2;
            right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

            total = (4 * left) + (2 * middle) + right;

            /* ========= Determine the color of the active cell ========= */
            current[i] += (rule_1 >> (total)) & 1;

            /* ===== Determine the displacement of the active cell ====== */
            if ((rule_2 >> total) & 1) {
                current[((i - 1) < 0) ? size - 1 : i - 1] += 2; 
            }
            else {
                current[((i + 1) >= size) ? 0 : i + 1] += 2; 
            }
        }
        else {
            current[i] += previous[i];
        }
    }

    /* ================================ */

    return ;
}