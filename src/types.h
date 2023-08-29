#ifndef NKS_DATA_H
#define NKS_DATA_H

#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "../ps-sdl-wrapper/src/core.h"
#include "../ps-sdl-wrapper/src/types.h"

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/* Turing machine weight */
#define TM_WEIGHT 3

#define FILENAME_SIZE 64

#define STATE_LEN 16

/**
 * The size of a buffer used to indicated the maximum number of digits in a number convered from a decimal system to a specified one
*/
#define BUFFER_SIZE 32



/**
    * States of the Turing machine head
*/
enum states {
    STATE_0 = 0,
    STATE_1 = 1,
};



/* Types of cellular automata that can be used */
enum CA_types {
    ELEMENTARY = 0,
    TOTALISTIC3 = 1,
    MOBILE_O = 2,
    TURING_M = 3,
};



/** 
 * Different colors represent distinct states of the machine. The read/write head is represented as a circle
*/
static SDL_Color head_states[] = {
    {0x00, 0xff, 0x00, 0xff}, /* State 0. Green */
    {0x00, 0x00, 0xff, 0xff}, /* State 1. Blue */
};



/**
 * Available colors
*/
static SDL_Color __colors[] = {
    {0xff, 0xff, 0xff, 0xff}, /* White */
    {0xff, 0x00, 0x00, 0xff}, /* Red */
    {0x00, 0x00, 0x00, 0xff}, /* Black */
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

/* Applicatipon data type. Aggregate all the data related to a cellular automaton that is currently being explored */
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

    /* A 2-state 3-symbol Turing machine */
    struct __turing_machine {
        /* Number of states */
        size_t n_states;

        unsigned char current_state;

        /* Strings of states/rules */
        char states[2][STATE_LEN];
    } machine;
} App;

/* ================================================================ */

#endif /* NKS_DATA_H */