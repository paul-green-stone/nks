#include "src/data.h"

#include <limits.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

/* ================================ */

#define OPTSTRING ":x:y:g"

/* ================================ */

void swap(char* a, char* b, size_t size);

void print_usage_message(const char* caller_name);

/* ================================ */

/* Function pointer typedef */
typedef void (*rule)(unsigned char* current, unsigned char* previous, size_t size);

int main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    App app = {
        .width = 480,
        .height = 480,
        .cell_size = 8,
        .speed = 60,
        .rule = -1,
        .generation = 0,
    };

    /* Current generation */
    unsigned char* current;

    /* Prvious generation */
    unsigned char* previous;

    /* Program exit code */
    int result = EXIT_SUCCESS;

    /* SDL event happened */
    SDL_Event event;

    /* Main loop controlling variable */
    char quit = 0;

    /* Time related variables  */
    uint64_t start = 0;
    float delta = 0;
    time_t t;

    /* Loop variable */
    size_t i = 0;

    /* Row and columns */
    size_t r = 0, c = 0;

    /* Current command line option */
    int option;

    /* Coordinates of a cell to be displayed */
    SDL_Rect cell = {0, 0, app.cell_size, app.cell_size};

    extern char* optarg;
    extern int optind, opterr, optopt;

    /* ================================ */



    while (1) {

        static struct option options[] = {
            {"cell", required_argument, NULL, 0},           /* Cell size */
            {"speed", required_argument, NULL, 0},          /* Number of steps every second */
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
                    app.cell_size = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 1) {
                    app.speed = (int) strtol(optarg, NULL, 10);

                    if (app.speed > 60) {
                        app.speed = 60;
                    }
                }
                else if (option_index == 2) {
                    app.lifespan = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 3) {
                    app.rule = (int) strtol(optarg, NULL, 10) % 255;
                }
                else if (option_index == 4) {
                    app.random_start_init = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 5) {
                    print_usage_message(argv[0]);

                    return result;
                }

                break ;

            /* Turn on the grid */
            case 'g':
                app.is_grid = !app.is_grid;

                break ;

            /* Set window width */
            case 'x':
                app.width = (int) strtol(optarg, NULL, 10);      

                break ;

            /* Set a window height */
            case 'y':
                app.height = (int) strtol(optarg, NULL, 10);

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
    app.width = ((app.width % app.cell_size) == 0) ? app.width : app.width - (app.width % app.cell_size);

    /* Compute a new window height */
    app.height = ((app.height % app.cell_size) == 0) ? app.height : app.height - (app.height % app.cell_size);



    /* ================ Dynamically allocate a 2D array ================ */

    /* Compute the number of rows */
    app.rows = app.height / app.cell_size;

    /* Compute the number of columns */
    app.columns = app.width / app.cell_size;


    app.grid = (unsigned char**) malloc(sizeof(unsigned char*) * app.rows);

    for (i = 0; i < app.rows; i++) {
        app.grid[i] = (char*) malloc(sizeof(unsigned char*) * app.columns);

        memset(app.grid[i], 0, sizeof(unsigned char*) * app.columns);
    }

    i = 0;

    /* ================================================================= */

    /* Update a cell */
    cell.w = cell.h = app.cell_size;

    /* Update time interval */
    app.speed = (1000. / app.speed) / 1000.;

    /* Update a new lifespan */
    app.lifespan = (app.lifespan == 0) ? app.height / app.cell_size : app.lifespan;


    /* Random number generator initialization */
    srand((unsigned) time(&t));

    if (app.random_start_init) {

        for (i = 0; i < app.random_start_init; i++) {
            app.grid[0][rand() % app.columns] = 1;
        }
    }
    else {
        app.grid[0][app.columns / 2] = 1;
    }

    i = 0;

    app.rule = (app.rule == -1) ? rand() % 255 : app.rule;

    /* ================================ */

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0) {

        if ((app.window = Window_create("anks-ca", app.width, app.height, SDL_WINDOW_SHOWN, RENDERER, SDL_RENDERER_ACCELERATED)) != NULL) {

            /* Get a window context */
            app.context = Window_get_context(app.window);

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

                /* =================== Render starts here =================== */
                
                /* Set color to white */
                Global_set_color(0xff, 0xff, 0xff, 0xff);

                /* Fill the window with white */
                Window_clear(app.window);

                /* Set color to black */
                Global_set_color(0x00, 0x00, 0x00, 0xff);

                /* Display a grid if specified */
                if (app.is_grid) {
                    Window_display_grid(app.window, app.cell_size);
                }
                


                /* ============== Display a cellular automaton ============== */

                for (r = 0; r < app.rows; r++) {

                    for (c = 0; c < app.columns; c++) {

                        if (app.grid[r][c]) {

                            cell.x = c * app.cell_size * 1;
                            cell.y = r * app.cell_size * 1;

                            Rect_fill(&cell);
                        }
                    }
                }


                
                /* ============== Update a cellular automaton =============== */

                if (app.generation < app.lifespan - 1) {

                    if (delta >= app.speed) {

                        delta = 0;

                        app.generation++;

                        current = app.grid[app.generation];
                        previous = app.grid[app.generation - 1];
                        
                        /* Apply a rule */
                        apply_CA_rule_N(current, previous, app.columns, app.rule);
                    }
                }
                
                /* Update the screen */
                Window_update(app.window);

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



    Window_destroy(&app.window);
    SDL_Quit();

    free(app.grid);

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

/* ================================ */

void print_usage_message(const char* caller_name) {

    fprintf(stderr, "usage: %s [-xyg] [--cell=<size>] [--speed=<number of steps in a second>] [--lifespan=<number>] [--rule=<CA rule>] [--start=<number>] [--help]\n", caller_name);

    return ;
}