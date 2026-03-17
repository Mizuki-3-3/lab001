#pragma once
#include <curses.h>
#include <panel.h>
#include <stdlib.h>
#include <math.h>

typedef struct cursed_window {
    WINDOW *background;
    WINDOW *overlay;
} curw;

void start_to_work(void);
curw *make_new_win(void);
void check_input_type(void);
