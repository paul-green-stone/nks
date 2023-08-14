#include "ps-sdl-wrapper/src/core.h"
#include "ps-sdl-wrapper/src/types.h"
#include "src/rules.h"

#include <limits.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

/* ================================ */



#define OPTSTRING ":x:y:gh"



/* ================================ */

void swap(char* a, char* b, size_t size);

void print_usage_message(const char* caller_name);

/* ================================ */

/* Function pointer typedef */
typedef void (*rule)(unsigned char* current, unsigned char* previous, size_t size);

/* An array of the rules currently available */
rule rules[] = {
    rule_0,
    rule_1,
    rule_2,
    rule_3,
    rule_4,
    rule_5,
    rule_6,
    rule_7,
    rule_8,
    rule_9,
    rule_10,
    rule_11,
    rule_12,
    rule_13,
    rule_14,
    rule_15,
    rule_16,
    rule_17,
    rule_18,
    rule_19,
};


int main(int argc, char** argv) {
    /* =========== VARIABLES ========== */


    /* Window appearing on the screen */
    Window_t window = NULL;

    /* Window rendering context */
    Context_t context = NULL;

    /* Window width. 480 by default */
    int width = 480;

    /* Window height. 480 by default */
    int height = 480;

    /* Grid controlling variable */
    char is_grid = 0;

    /* Cell size. 8 by default */
    int cell_size = 8;

    /* Time interval between two generations. 0.3 by default */
    float interval = 0.3;

    /* Rule to apply */
    int rule = -1;
    
    /* Ramdom start initials */
    int random_start_init = 0;

    /* Current generation */
    unsigned char* current = NULL;

    /* Prvious generation */
    unsigned char* previous = NULL;

    /* Size of arrays */
    size_t size;


    /* Program exit code */
    int result = EXIT_SUCCESS;


    /* SDL event happened */
    SDL_Event event;


    /* Main loop controlling variable */
    char quit = 0;

    /* Time related variables  */
    uint64_t start = 0;
    float delta = 0;

    /* Loop traversing variable */
    size_t i = 0;

    /* Current command line option */
    int option;


    /* Current generation */
    int generation = 0;

    /* Number of generations to produce */
    int lifespan = 0;


    /* Coordinates of a cell to be displayed */
    SDL_Rect cell = {0, 0, cell_size, cell_size};


    extern char* optarg;
    extern int optind, opterr, optopt;

    time_t t;

    /* ================================ */



    while (1) {

        static struct option options[] = {
            {"cell", required_argument, NULL, 0},           /* Cell size */
            {"interval", required_argument, NULL, 0},       /* Time interval between two generations */
            {"lifespan", required_argument, NULL, 0},       /* Number of generations a cellular automata has */
            {"rule", required_argument, NULL, 0},           /* Rule to apply */
            {"start", required_argument, NULL, 0},          /* Number of start initials */
            {"help", no_argument, NULL, 0},
            {NULL, 0, NULL, 0},
        };

        int option_index;

        option = getopt_long(argc, argv, OPTSTRING, options, &option_index);

        /* ================================ */

        if (option == -1) {
            break ;
        }

        /* ================================ */


        switch (option) {
            case 0:

                if (option_index == 0) {
                    cell_size = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 1) {
                    interval = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 2) {
                    lifespan = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 3) {
                    rule = (int) strtol(optarg, NULL, 10) % 255;
                }
                else if (option_index == 4) {
                    random_start_init = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 5) {
                    print_usage_message(argv[0]);

                    return result;
                }

                break ;

            /* Turn on the grid */
            case 'g':
                is_grid = !is_grid;

                break ;

            /* Set window width */
            case 'x':
                width = (int) strtol(optarg, NULL, 10);      

                break ;

            /* Set a window height */
            case 'y':
                height = (int) strtol(optarg, NULL, 10);

                break ;

            case 'h':
                print_usage_message(argv[0]);

                return result;

            case '?':
                fprintf(stderr, "Unknown option %c\n", optopt);

                print_usage_message(argv[0]);

                return EXIT_FAILURE;

            case ':':
                fprintf(stderr, "Missing arg for %c\n", optopt);

                print_usage_message(argv[0]);

                return EXIT_FAILURE;

            default:
                printf("?? getopt returned character code 0%o ??\n", option_index);

                break ;
        }
    }

    /* Compute a new window width */
    width = ((width % cell_size) == 0) ? width : width - (width % cell_size);

    /* Compute a new window height */
    height = ((height % cell_size) == 0) ? height : height - (height % cell_size);

    /* Compute a size of a dynamically allocated array */
    size = sizeof(char) * width / cell_size;

    /* Update a cell */
    cell.w = cell.h = cell_size;

    /* Update time interval */
    interval = interval / 1000;

    /* Update a new lifespan */
    lifespan = (lifespan == 0) ? height / cell_size : lifespan;



    if (((current = (unsigned char*) malloc(sizeof(char) * (width / cell_size)))) && (previous = (unsigned char*) malloc(sizeof(char) * (width / cell_size))) != NULL) {

        memset(current, 0, sizeof(char) * (width / cell_size));
        memset(previous, 0, sizeof(char) * (width / cell_size));

        /* Random number generator initialization */
        srand((unsigned) time(&t));

        if (random_start_init) {
            for (; i < random_start_init; i++) {
                current[rand() % size] = 1; 
            }
        }
        else {
            current[sizeof(char) * (width / cell_size) / 2] = 1;
        }

        i = 0;

        rule = (rule == -1) ? rand() % 9 : rule;
    }

    /* ================================ */

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0) {

        if ((window = Window_create("anks-ca", width, height, SDL_WINDOW_SHOWN, RENDERER, SDL_RENDERER_ACCELERATED)) != NULL) {

            /* Get a window context */
            context = Window_get_context(window);

            Global_set_color(0xff, 0xff, 0xff, 0xff);

            Window_clear(window);

            Global_set_color(0x00, 0x00, 0x00, 0xff);

            if (is_grid) {
                Window_display_grid(window, cell_size);
            }

            /* ================================ */
            
            while (!quit) {

                start = SDL_GetTicks64();

                while (SDL_PollEvent(&event) > 0) {

                    switch (event.type) {
                        case SDL_QUIT:
                            quit = !quit;

                            break ;
                    }
                }

                /* Render starts here */

                if (generation < lifespan) {

                    if (delta >= interval) {

                        /* Traverse an array of cells */
                        for (; i < size; i++) {
                            
                            if (current[i]) {
                                cell.x = i * cell_size * (current[i] > 0);
                                cell.y = generation * cell_size * (current[i] > 0);
                                
                                Rect_fill(&cell);
                            }
                        }

                        delta = 0;
                    }

                    if (i >= size) {
                        generation++;

                        i = 0;

                        swap(current, previous, size);

                        rules[rule](current, previous, width / cell_size);
                    }
                }

                Window_update(window);

                delta += (SDL_GetTicks64() - start) / 1000.0f;
            } 
        }
        else {
            result = EXIT_FAILURE;
        }
    }
    else {
        warn_with_sys_msg(SDL_GetError());

        result = EXIT_FAILURE;
    }



    Window_destroy(&window);
    SDL_Quit();

    free(current);
    free(previous);

    /* ================================ */

    return result;
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

void print_usage_message(const char* caller_name) {

    fprintf(stderr, "usage: %s [-xygh] [--cell=<size>] [--interval=<ms>] [--lifespan=<number>] [--rule=<CA rule>] [--start=<number>] [--help]\n", caller_name);

    return ;
}