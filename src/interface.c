#include "interface.h"

void start_to_work(){
    initscr(); // инициализируем библиотеку
    cbreak();  // Не использовать буфер для функции getch()
    noecho(); // Не печатать на экране то, что набирает пользователь на клавиатуре
    keypad(stdscr, TRUE); // Активировать специальные клавиши клавиатуры
    raw();
    nonl();//////////////////
    if (has_colors() == FALSE) {
        endwin();
        puts("\nYour terminal does not support color");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    
}

curw *make_new_win() {
    curw *new = malloc(sizeof(curw));
    attron(COLOR_PAIR(1));
    if (!new) return NULL;
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    new->background = newwin(max_y, max_x, 0, 0);
    wbkgd(new->background, COLOR_PAIR(1));
    box(new->background, 0, 0);
    mvwaddstr(new->background, 0, max_x/2-6, "~~VECTORS~~");
    wrefresh(new->background);
    
    new->overlay = derwin(new->background, max_y-3, max_x-2, 2, 1);
    if (!new->overlay) {
        delwin(new->background);
        free(new);
        return NULL;
    }
    wbkgd(new->overlay, COLOR_PAIR(1));
    box(new->overlay,0,0);
    wrefresh(new->overlay);
    return new;
}

void check_input_type(){
    char input[100] = "";
    double x;
    int num;
    int assignment[5] = {0};
    double tolerance = 1e-12;

    printf("Pls. provide input: ");
    fgets(input, 100, stdin);

    if (sscanf(input, "%lf", &x) == 1) {
        // Is it a number? All integers are also doubles.
        num = (int)x; // We cast to int. 
        if ( fabs(x - num)/x > tolerance ) {
            printf("The input is a floating point\n");
        } else { 
            printf("The input is a integer\n");
        }
    } else { 
      // No match error.
        printf("input not recognized\n");
    }
}