#ifndef INTERFACE_H
#define INTERFACE_H

#include <curses.h>
#include <panel.h>
#include <stdlib.h>
#include <math.h>

typedef struct cursed_window {
    WINDOW *background;
    WINDOW *overlay;
} curw;

void start_to_work();
curw *make_new_win();
void check_input_type();

#endif