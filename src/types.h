#ifndef ANKS_DATA_H
#define ANKS_DATA_H

#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>

#include "../ps-sdl-wrapper/src/core.h"
#include "../ps-sdl-wrapper/src/types.h"

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

#define FILENAME_SIZE 64

/**
 * The size of a buffer used to indicated the maximum number of digits in a number convered from a decimla system to a specified one
*/
#define BUFFER_SIZE 32



/* Types of cellular automata that can be used */
enum CA_types {
    ELEMENTARY = 0,
    TOTALISTIC3 = 1,
    MOBILE_O = 2,
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/* Applicatipon data type. Aggregate all the data related to a cellular automaton is currently being explored */
typedef struct __application {

    /* ================================ */
    /* == Window physical properties == */
    /* ================================ */

    /* Window appearing on the screen */
    Window_t window;

    /* Rendering context used by the window */
    Context_t context;

    /* Window width */
    int width;

    /* Window height */
    int height;



    /* ================================ */
    /* === Grid physical properties === */
    /* ================================ */

    /* Grid controlling variable */
    char is_grid;

    /* Number of rows */
    ssize_t rows;

    /* Number of columns */
    ssize_t columns;

    /* Cell size */
    int cell_size;

    /* A dynamically allocated 2D array */
    unsigned char** grid;



    /* ================================ */
    /* ======== CA properties  ======== */
    /* ================================ */

    /* Number of generations a second */
    int speed;

    /* Rule to apply */
    int rule;
    /* Mobile automata rule used to identify the displacement of an active cell */
    int mrule;
    
    /* Number of cells initialized at the start */
    int random_start_init;

    /* Current generation */
    int generation;

    /* Number of generations to produce */
    int lifespan;

    /* CA type */
    int type;
} App;

/* ================================================================ */

#endif /* ANKS_DATA_H */