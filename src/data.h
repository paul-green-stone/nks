#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <sys/types.h>

#include "../ps-sdl-wrapper/src/core.h"
#include "../ps-sdl-wrapper/src/types.h"
#include "rules.h"

typedef struct __application {
    /* Window appearing on the screen */
    Window_t window;

    /* Rendering context used by the window */
    Context_t context;

    /* Window width */
    int width;

    /* Window height */
    int height;

    /* Grid controlling variable */
    char is_grid;

    /* Cell size. 8 by default */
    int cell_size;

    /* Number of steps every second */
    float speed;

    /* Rule to apply */
    int rule;
    
    /* Random start initials */
    int random_start_init;

    /* Number of rows */
    size_t rows;

    /* Number of columns */
    size_t columns;

    /* A dynamically allocated 2D array */
    unsigned char** grid;

    /* Current generation */
    int generation;

    /* Number of generations to produce */
    int lifespan;
} App;

#endif /* DATA_H */