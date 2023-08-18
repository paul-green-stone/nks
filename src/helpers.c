#include "helpers.h"

/* ================================================================ */

unsigned char* d2t(size_t number) {
    /* =========== VARIABLES ========== */

    size_t i = 0;

    unsigned char* rule;

    /* Remainder */
    int r;

    printf("%d\n", number);

    /* ================================ */

    if ((rule = (unsigned char*) malloc(sizeof(char) * TCA3_SIZE)) != NULL) {

        for (; i < TCA3_SIZE; i++) {

            /* Value to put in the array */
            r = number % 3;

            number /= 3;

            rule[i] = r + '0';
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

    fprintf(stderr, "usage: %s [-xyg] [--cell=<size>] [--speed=<number of steps in a second>] [--lifespan=<number>] [--rule=<CA rule>] [--start=<number>] [--help] [--type=<number>]\n", caller_name);

    return ;
}

/* ================================================================ */

void App_info(struct __application* app) {

    if (app != NULL) {

        /* ================================ */
        /* ======== CA properties  ======== */
        /* ================================ */

        printf("%-16s: ", "type");

        switch (app->type) {

            case ELEMENTARY:
                printf("ELEMENTARY\n");

                break ;

            case TOTALISTIC3:
                printf("TOTALISTIC3\n");

                break ;
        }

        printf("%-16s: %d\n", "rule", app->rule);
        printf("%-16s: %d\n", "cell size", app->cell_size);
        printf("%-16s: %d\n", "speed", app->speed);
        printf("%-16s: %d\n", "lifespan", app->lifespan);
        printf("%-16s: %lld\n", "cells", app->rows * app->columns);
        printf("%-16s: %lld\n", "rows", app->rows);
        printf("%-16s: %lld\n", "columns", app->columns);
        printf("%-16s: %s\n", "grid", (app->is_grid) ? "on (1)" : "off (0)");

        /* ================================ */

        printf("%-16s: %s\n", "random start", (app->random_start_init > 0) ? "on (1)" : "off (0)");

        if (app->random_start_init > 0) {
            printf("\t%s: %lld\n", "init cells", app->random_start_init);
        }

        /* ================================ */

        printf("\n%-16s: %d\n", "width", app->width);
        printf("%-16s: %d\n", "height", app->height);
    }

    return ;
}