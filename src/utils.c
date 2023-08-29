#include "utils.h"

#include <strings.h>

/* ================================================================ */

unsigned char* d2B(size_t number, int base) {
    /* =========== VARIABLES ========== */

    size_t i = 0;

    unsigned char* rule;

    /* Remainder */
    int r;

    /* ================================ */

    if ((rule = (unsigned char*) malloc(sizeof(char) * BUFFER_SIZE)) != NULL) {

        memset(rule, 0, BUFFER_SIZE);

        for (; number > 0; i++) {

            /* Value to put in the array */
            r = number % base;

            number /= base;

            rule[i] = r + '0';
        }

        for (; i < BUFFER_SIZE; i++) {
            rule[i] = '0';
        }

        rule[BUFFER_SIZE - 1] = '\0';
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================ */
    
    return rule;
}

/* ================================================================ */

void swap(char* a, char* b, size_t size) {
    /* =========== VARIABLES ========== */

    char temp;

    size_t i = 0;

    for (; i < size; i++) {
        temp = a[i];

        a[i] = b[i];
        b[i] = temp;
    }

    return ;
}

/* ================================================================ */

void print_usage_message(const char* caller_name) {

    fprintf(stdout, "usage: %s [options] output\n", caller_name);

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
    fprintf(stdout, "\n\t%-16s\t%-32s\n", "", "Values:");
    fprintf(stdout, "\t%-16s\t%-32s\n", " ", "ELEMENTARY [0]: a one-dimensional automaton with two possible states for each cell");
    fprintf(stdout, "\t%-16s\t%-32s\n", " ", "TOTALISTIC3 [1]: a one-dimensional automaton with three possible states for each cell");
    fprintf(stdout, "\t%-16s\t%-32s\n", " ", "MOBILE_O [2]: a one-dimensional automaton similar to cellular automata but which have a single \"active\" cell instead of updating all cells in parallel.");
    fprintf(stdout, "\t%-16s\t%-32s\n\n", " ", "TURING_M [3]: an abstract machine that manipulates symbols on a strip of tape according to a table of rules.");

    fprintf(stdout, "\t%-16s\t%-32s\n", "--mrule=<n>", "Set the rule defining the displacement of an active cell");

    fprintf(stdout, "\n\t%-16s\n\n", "================================================================");

    /* ======================== Example ========================= */
    fprintf(stdout, "\nExample:\n\t%s -x800 -g --cell=6 --rule=30 --type=1\n", caller_name);
    fprintf(stdout, "\n");

    /* ================================ */

    return ;
}

/* ================================================================ */

void App_info(struct __application* app) {
    /* =========== VARIABLES ========== */

    size_t width = 64;

    /* Padding to center the text */
    int padding;

    char* type = NULL;

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

            case MOBILE_O:
                type = strdup("MOBILE_O");

                break ;

            case TURING_M:
                type = strdup("TURING_M");

                break ;


            default:
                type = strdup("UNKNOWN");

                break ;
        }

        fprintf(stdout, "   %-29s:%29s\n", "type", type);
    }

    /* ================================ */

    if (app->type != TURING_M) {
        fprintf(stdout, "   %-29s:%29d\n", "rule", app->rule);
    }

    if (app->type == MOBILE_O) {
        fprintf(stdout, "      %-26s:%26d\n", "mrule", app->mrule);
    }
    else if (app->type == TURING_M) {
        fprintf(stdout, "      %-26s:%26ld\n", "states", app->machine.n_states);
    }

    fprintf(stdout, "   %-29s:%29s\n", "grid", (app->is_grid) ? "on" : "off");
    fprintf(stdout, "   %-29s:%29d\n", "cell", app->cell_size);
    fprintf(stdout, "   %-29s:%29ld\n", "rows", app->rows);
    fprintf(stdout, "   %-29s:%29ld\n", "columns", app->columns);
    fprintf(stdout, "   %-29s:%29d\n", "speed", app->speed);
    fprintf(stdout, "   %-29s:%29d\n", "lifespan", app->lifespan);
    fprintf(stdout, "   %-29s:%29ld\n", "total", app->rows * app->columns);
    
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

/* ================================================================ */

void parse_XML_states(const App* app, const char* filename) {
    /* =========== VARIABLES ========== */

    /* A structure containing the tree */
    xmlDocPtr document;

    xmlNodePtr current_node;

    xmlChar* node_cnt;

    xmlChar* state;

    /* ================================ */

    if ((document = xmlParseFile(filename)) != NULL) {

        if ((current_node = xmlDocGetRootElement(document)) != NULL) {

            if (xmlStrcmp(current_node->name, (const xmlChar*) "turing_machine")) {

                warn_with_user_msg(__func__, "document of the wrong type");

                return ;
            }
            else {
                current_node = current_node->children;

                while (current_node != NULL) {

                    if ((!xmlStrcmp(current_node->name, (const xmlChar*) "state"))) {
                        
                        node_cnt = xmlNodeListGetString(document, current_node->children, 1);
                        
                        if (node_cnt) {
                            state = xmlGetProp(current_node, (xmlChar*) "state");

                            strcpy(app->machine.states[(int) strtol((char*) state, NULL, 10)], (char*) node_cnt);
                        }
                        
                    }

                    current_node = current_node->next;
                }
            }
        }
        else {

        }
    }
    else {
        warn_with_user_msg(__func__, "Document not parsed successfully");

        return ;
    }
    
    /* ================================ */

    return ;
}