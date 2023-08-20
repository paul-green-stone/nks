#include "utils.h"

#include <strings.h>

/* ================================================================ */

unsigned char* d2t(size_t number) {
    /* =========== VARIABLES ========== */

    size_t i = 0;

    unsigned char* rule;

    /* Remainder */
    int r;

    /* ================================ */

    if ((rule = (unsigned char*) malloc(sizeof(char) * TCA3_SIZE)) != NULL) {

        memset(rule, 0, TCA3_SIZE);

        for (; number > 0; i++) {

            /* Value to put in the array */
            r = number % 3;

            number /= 3;

            rule[i] = r + '0';
        }

        for (; i < TCA3_SIZE; i++) {
            rule[i] = '0';
        }

        rule[TCA3_SIZE] = '\0';
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================ */
    
    return rule;
}

/* ================================================================ */

void swap(char* a, char* b, size_t size) {
    char temp;

    for (int i = 0; i < size; i++) {
        temp = a[i];

        a[i] = b[i];
        b[i] = temp;
    }

    return ;
}

/* ================================================================ */

void print_usage_message(const char* caller_name) {

    fprintf(stdout, "usage: %s [options]\n", caller_name);

    fprintf(stdout, "\nOptions:\n");

    /* ===================== Short options ====================== */
    fprintf(stdout, "\t%-16s\t%-32s\n", "-x <width>", "Set the window width");
    fprintf(stdout, "\t%-16s\t%-32s\n", "-y <height>", "Set the window height");
    fprintf(stdout, "\t%-16s\t%-32s\n", "-g", "Display the grid");

    fprintf(stdout, "\n\t%-16s\n\n", "================================================================");

    /* ====================== Long options ====================== */
    fprintf(stdout, "\t%-16s\t%-32s\n", "-h --help", "Display this message");
    fprintf(stdout, "\t%-16s\t%-32s\n", "--cell=<n>", "Set the size of a single cell");
    fprintf(stdout, "\t%-16s\t%-32s\n", "--speed=<n>", "Set the number of generations per second");
    fprintf(stdout, "\t%-16s\t%-32s\n", "--lifespan=<n>", "Set the total number of generations");
    fprintf(stdout, "\t%-16s\t%-32s\n", "--rule=<n>", "Set the rule number to apply");
    fprintf(stdout, "\t%-16s\t%-32s\n", "--start=<n>", "Set the number of cells randomly initialized in the first generation");

    fprintf(stdout, "\n\t%-16s\t%-32s\n", "--type=<n>", "Set the type of the automaton");
    fprintf(stdout, "\t%-16s\t%-32s\n", " ", "ELEMENTARY [0]: a one-dimensional automaton with two possible states for each cell");
    fprintf(stdout, "\t%-16s\t%-32s\n", " ", "TOTALISTIC3 [1]: a one-dimensional automaton with three possible states for each cell");

    fprintf(stdout, "\n\t%-16s\n\n", "================================================================");

    /* ======================== Example ========================= */
    fprintf(stdout, "\nExample:\n\t%s -x800 -g --cell=6 --rule=30 --type=1\n", caller_name);
    fprintf(stdout, "\n");

    /* ================================ */

    return ;
}

/* ================================================================ */

void App_info(struct __application* app) {

    size_t width = 64;

    /* Padding to center the text */
    int padding;

    char* type;

    if (app != NULL) {

        padding = (width - strlen("Cellular Automaton Information")) / 2;

        fprintf(stdout, "\n================================================================\n");
        fprintf(stdout, "%*s%s%*s", padding, "", "Cellular Automaton Information", padding, "");
        fprintf(stdout, "\n================================================================\n");

        /* ================================ */

        /* ========== Determine the propper automaton type ========== */
        switch (app->type) {
            
            case ELEMENTARY:
                type = strdup("ELEMENTARY");

                break ;

            case TOTALISTIC3:
                type = strdup("TOTALISTIC3");

                break ;

            default:
                type = strdup("UNKNOWN");

                break ;
        }

        fprintf(stdout, "   %-29s:%29s\n", "type", type);
    }

    /* ================================ */

    fprintf(stdout, "   %-29s:%29d\n", "rule", app->rule);
    fprintf(stdout, "   %-29s:%29s\n", "grid", (app->is_grid) ? "on" : "off");
    fprintf(stdout, "   %-29s:%29d\n", "cell", app->cell_size);
    fprintf(stdout, "   %-29s:%29d\n", "rows", app->rows);
    fprintf(stdout, "   %-29s:%29d\n", "columns", app->columns);
    fprintf(stdout, "   %-29s:%29d\n", "speed", app->speed);
    fprintf(stdout, "   %-29s:%29d\n", "lifespan", app->lifespan);
    fprintf(stdout, "   %-29s:%29d\n", "total", app->rows * app->columns);
    
    fprintf(stdout, "   %-29s:%29s\n", "start", (app->random_start_init > 0) ? "on" : "off");

    if (app->random_start_init > 0) {
        fprintf(stdout, "      %-26s:%26d\n", "cells", app->random_start_init);
    }

    fprintf(stdout, "\n   %-29s:%29d\n", "width", app->width);
    fprintf(stdout, "   %-29s:%29d\n", "height", app->height);

    fprintf(stdout, "================================================================\n");

    /* ================================ */

    free(type);

    /* ================================ */

    return ;
}