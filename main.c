#include "src/types.h"
#include "src/rules.h"
#include "src/utils.h"

#include <limits.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

/* ================================ */

#define OPTSTRING ":x:y:gh"

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
        .random_start_init = 0,
        .type = ELEMENTARY,
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

    unsigned char* rule = NULL;

    float interval;

    /* ================================ */



    /* ================== Command line parsing ================== */
    while (1) {

        /* ========================================================== */
        /* ============= Parameters the program accepts ============= */
        /* ========================================================== */

        static struct option options[] = {
            {"cell", required_argument, NULL, 0},           /* Cell size */
            {"speed", required_argument, NULL, 0},          /* Number of steps every second */
            {"lifespan", required_argument, NULL, 0},       /* Number of generations a cellular automata has */
            {"rule", required_argument, NULL, 0},           /* Rule to apply */
            {"start", required_argument, NULL, 0},          /* Number of start initials */
            {"help", no_argument, NULL, 0},
            {"type", required_argument, NULL, 0},           /* One of the values of CA variations */
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

                    /* ========== Check for validity of the cell size =========== */
                    if (app.cell_size < 1) {
                        app.cell_size = 2;
                    }
                }
                else if (option_index == 1) {
                    app.speed = (int) strtol(optarg, NULL, 10);

                    if ((app.speed > 60) || (app.speed < 1)) {
                        app.speed = 60;
                    }
                }
                else if (option_index == 2) {
                    app.lifespan = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 3) {
                    app.rule = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 4) {
                    app.random_start_init = (int) strtol(optarg, NULL, 10);
                }
                else if (option_index == 5) {
                    print_usage_message(argv[0]);

                    return result;
                }
                /* Set a CA type */
                else if (option_index == 6) {
                    app.type = (int) strtol(optarg, NULL, 10);

                    /* ======== Check for validity of the specified type ======== */
                    if ((app.type < 0) || (app.type > 1)) {

                        fprintf(stderr, "Unknown CA type\n");

                        print_usage_message(argv[0]);

                        return EXIT_FAILURE;
                    }
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

    /* ========================================================== */



    /* Compute a new window width */
    app.width = ((app.width % app.cell_size) == 0) ? app.width : app.width - (app.width % app.cell_size);

    /* Compute a new window height */
    app.height = ((app.height % app.cell_size) == 0) ? app.height : app.height - (app.height % app.cell_size);



    /* ========================================================== */
    /* ============ Dynamically allocate a 2D array ============= */
    /* ========================================================== */

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
    interval = (1000. / app.speed) / 1000.;

    /* Update a new lifespan */
    app.lifespan = (app.lifespan == 0) ? app.height / app.cell_size : app.lifespan;



    /* ========================================================== */
    /* =============== Setting initial conditions =============== */
    /* ========================================================== */

    /* ========= Random number generator initialization ========= */
    srand((unsigned) time(&t));

    if (app.random_start_init > 0) {

        for (i = 0; i < app.random_start_init; i++) {

            /* ==== All initial values are placed in the first generation ==== */
            app.grid[0][rand() % app.columns] = 1;
        }
    }
    else {

        /* Both ELEMENTARY and TOTALISTIC3 CA start with the cell of 1 in the middle of an array */
        if ((app.type == ELEMENTARY) || (app.type == TOTALISTIC3)) {
            app.grid[0][app.columns / 2] = 1;
        }
    }

    /* ========================================================== */
    /* ========== Rules are randomized if not specified ========= */
    /* ========================================================== */

    if (app.type == ELEMENTARY) {
        app.rule = (app.rule == -1) ? rand() % 255 : app.rule % 255;
    }
    else if (app.type == TOTALISTIC3) {

        /* App stores an integer version of the specified rule */
        app.rule = (app.rule == -1) ? rand() % 2187 : app.rule;

        /* Convert a decimal number into a ternary one (base 3 number). It is stored in reversed order */
        rule = d2t(app.rule);
    }

    i = 0;

    /* ================================================================ */



    /* ========================================================== */
    /* ================== Main things go here =================== */
    /* ========================================================== */

    /* ===== Displaying info about CA that's being explored ===== */
    App_info(&app);

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0) {

        if ((app.window = Window_create("nks", app.width, app.height, SDL_WINDOW_SHOWN, SURFACE, SDL_RENDERER_ACCELERATED)) != NULL) {

            /* Get a window context */
            app.context = Window_get_context(app.window);

            /* ================================ */
            
            while (!quit) {

                start = SDL_GetTicks64();



                /* ========================================================== */
                /* ====================== Handle input ====================== */
                /* ========================================================== */

                while (SDL_PollEvent(&event) > 0) {

                    switch (event.type) {
                        case SDL_QUIT:
                            quit = !quit;

                            break ;
                    }
                }



                /* ========================================================== */
                /* =================== Render starts here =================== */
                /* ========================================================== */
                
                /* =================== Set color to white =================== */
                Global_set_color(0xff, 0xff, 0xff, 0xff);

                /* =============== Fill the window with white =============== */
                Window_clear(app.window);

                /* =================== Set color to black =================== */
                Global_set_color(0x00, 0x00, 0x00, 0xff);

                /* ============== Display a grid if specified =============== */
                if (app.is_grid) {
                    Window_display_grid(app.window, app.cell_size);
                }
                


                /* ========================================================== */
                /* ============== Display a cellular automaton ============== */
                /* ========================================================== */

                for (r = 0; r < app.rows; r++) {

                    for (c = 0; c < app.columns; c++) {

                        if (app.grid[r][c]) {

                            cell.x = c * app.cell_size * 1;
                            cell.y = r * app.cell_size * 1;

                            if (app.type == TOTALISTIC3) {

                                (app.grid[r][c] == 1) ? Global_set_color(255, 0, 0, 255) : (app.grid[r][c] == 2) ? Global_set_color(0x00, 0x00, 0x00, 0xff) : Global_set_color(0xff, 0xff, 0xff, 0xff);
                            }

                            Rect_fill(&cell);
                        }
                    }
                }



                /* ========================================================== */
                /* ============== Update a cellular automaton =============== */
                /* ========================================================== */

                if (app.generation < app.lifespan - 1) {

                    if (delta >= interval) {

                        delta = 0;

                        app.generation++;

                        current = app.grid[app.generation];
                        previous = app.grid[app.generation - 1];
                        
                        /* Apply a rule */
                        (app.type == TOTALISTIC3) ? apply_3T_CA(current, previous, app.columns, rule) : apply_2E_CA(current, previous, app.columns, app.rule);
                    }
                }

                
                
                /* =================== Update the screen ==================== */
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



    /* ========================================================== */
    /* ============= Destroy whatever was allocated ============= */
    /* ========================================================== */

    Window_destroy(&app.window);

    for (i = 0; i < app.rows; i++) {
        free(app.grid[i]);
    }
    free(app.grid);

    free(rule);

    SDL_Quit();

    /* ================================ */

    return result;
}