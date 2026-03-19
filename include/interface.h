#pragma once
#include <curses.h>
#include <panel.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    WINDOW *win;
    char buffer[32];
    double *value;
} InputField;

typedef struct {
    WINDOW *background;
    WINDOW *overlay;
    InputField fields[4];
    WINDOW *result_win;
    int mode;// 0 - сложение, 1 - умножение
    double x1, y1, x2, y2;
    double result;// для умножения
    double res_x, res_y;// для сложения
    int active_field;
} curw;

int start_to_work(void);
curw* create_main_win(void);
void run_interface(curw *win);
void cleanup_interface(curw *win);