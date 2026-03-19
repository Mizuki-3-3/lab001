#include "interface.h"
#include "vector.h"

int start_to_work() {
    initscr();
    cbreak();
    noecho();
    raw();
    nonl();
    if (has_colors() == FALSE) {
        endwin();
        puts("Terminal does not support color");
        return 1;
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    curs_set(0);
    return 0;
}

curw* create_main_win() {
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    int min_width = 60;
    int min_height = 15;
    if (max_x < min_width || max_y < min_height) {
        endwin();
        printf("Terminal too small. Need at least %dx%d\n", min_width, min_height);
        return NULL;
    }

    curw *new = malloc(sizeof(curw));
    if (!new) return NULL;

    new->background = newwin(max_y, max_x, 0, 0);
    wbkgd(new->background, COLOR_PAIR(1));
    box(new->background, 0, 0);
    mvwaddstr(new->background, 1, max_x / 2 - 6, "~~VECTORS~~");
    for (int i = 1; i<max_x-1; i++){
        mvwaddch(new->background, 2, i, ACS_HLINE);    
    }
    mvwaddch(new->background, 2, 0, ACS_LTEE);
    mvwaddch(new->background, 2, max_x-1, ACS_RTEE);
    wrefresh(new->background);

    new->overlay = derwin(new->background, max_y - 4, max_x - 2, 3, 1);
    if (!new->overlay) {
        delwin(new->background);
        free(new);
        return NULL;
    }
    wbkgd(new->overlay, COLOR_PAIR(1));

    init_input_fields(new);
    mvwaddstr(new->overlay, 4, 2, "введите координаты 1 вектора");
    mvwaddstr(new->overlay, 5, 3, "x:");
    mvwaddstr(new->overlay, 7, 3, "y:");
    mvwaddstr(new->overlay, 8, 2, "введите координаты 2 вектора");
    mvwaddstr(new->overlay, 10, 3, "x:");
    mvwaddstr(new->overlay, 12, 3, "y:");
    draw_mode_line(new);
    draw_fields(new);
    draw_result(new);
    wrefresh(new->overlay);
    wrefresh(new->background);
    keypad(new->overlay, TRUE);
    return new;
}

static int is_valid_number(const char *s, double *out) {
    char *end;
    *out = strtod(s, &end);
    return (end != s && *end == '\0');
}//проверка ввели число или лабуду

static int is_integer(double x) {
    return fabs(x - round(x)) < 1e-12;
}

static void update_result(curw *win) {
    int all_int = is_integer(win->x1) && is_integer(win->y1) && is_integer(win->x2) && is_integer(win->y2);
    if (all_int) {
        int *px1 = malloc(sizeof(int)); *px1 = (int)win->x1;
        int *py1 = malloc(sizeof(int)); *py1 = (int)win->y1;
        int *px2 = malloc(sizeof(int)); *px2 = (int)win->x2;
        int *py2 = malloc(sizeof(int)); *py2 = (int)win->y2;

        vector v1 = new_vector(px1, py1, all_int);
        vector v2 = new_vector(px2, py2, all_int);

        if (!win->mode) {
            vector *res = add(&v1, &v2);
            if (res) {
                win->res_x = *(int*)res->x;
                win->res_y = *(int*)res->y;
                del_vector(res);
            } else {
                win->res_x = win->res_y = 0;
            }
        } else { // умножение
            int res;
            if (multip(&v1, &v2, &res)) {
                win->result = res;
            } else {
                win->result = 0;
            }
        }
    } else {
        double *px1 = malloc(sizeof(double)); *px1 = win->x1;
        double *py1 = malloc(sizeof(double)); *py1 = win->y1;
        double *px2 = malloc(sizeof(double)); *px2 = win->x2;
        double *py2 = malloc(sizeof(double)); *py2 = win->y2;

        vector v1 = new_vector(px1, py1, 0);
        vector v2 = new_vector(px2, py2, 0);

        if (!win->mode) {
            vector *res = add(&v1, &v2);
            if (res) {
                win->res_x = *(double*)res->x;
                win->res_y = *(double*)res->y;
            } else {
                win->res_x = win->res_y = 0;
            }
        } else {
            double res;
            if (multip(&v1, &v2, &res)) {
                win->result = res;
            } else {
                win->result = 0;
            }
        }
    }
}

static void format(double val, char *buf, size_t size) {
    if (is_integer(val)) {
        snprintf(buf, size, "%d", (int)round(val));
    } else {
        snprintf(buf, size, "%g", val);
    }
}

void draw_result(curw *win) {
    werase(win->result_win);
    char buf[64];
    if (!win->mode) {
        char xs[32], ys[32];
        format(win->res_x, xs, sizeof(xs));
        format(win->res_y, ys, sizeof(ys));
        snprintf(buf, sizeof(buf), "{%s, %s}", xs, ys);
    } else {
        format(win->result, buf, sizeof(buf));
    }
    mvwaddstr(win->result_win, 0, (getmaxx(win->result_win) - strlen(buf)) / 2, buf);
    wrefresh(win->result_win);
}

void draw_fields(curw *win) {
    for (int i = 0; i < 4; i++) {
        InputField *f = &win->fields[i];
        werase(f->win);
        mvwprintw(f->win, 0, 1, "%s", f->buffer);
        if (i == win->active_field) {
            // Курсор в конец строки
            int x = 1 + strlen(f->buffer);
            wmove(f->win, 0, x);
        }
        wrefresh(f->win);
    }
}

void draw_mode_line(curw *win) {
    int maxx = getmaxx(win->overlay);
    int start_y = 1;
    mvwhline(win->overlay, start_y, 1, ' ', maxx - 2);
    const char *mode1 = " векторное сложение ";
    const char *mode2 = " скалярное умножение ";
    int len1 = strlen(mode1);
    int len2 = strlen(mode2);
    int total_len = len1 + len2;
    int start_x = (maxx - total_len) / 2;
    if (start_x < 1) start_x = 1;

    if (win->mode == 0) {
        wattron(win->overlay, A_REVERSE);
        mvwaddstr(win->overlay, start_y, start_x, mode1);
        wattroff(win->overlay, A_REVERSE);
        mvwaddstr(win->overlay, start_y, start_x + len1, mode2);
    } else {
        mvwaddstr(win->overlay, start_y, start_x, mode1);
        wattron(win->overlay, A_REVERSE);
        mvwaddstr(win->overlay, start_y, start_x + len1, mode2);
        wattroff(win->overlay, A_REVERSE);
    }
}

void init_input_fields(curw *win) {
    int maxy = getmaxy(win->overlay);
    int maxx = getmaxx(win->overlay);
    int ys[] = {5, 7, 10, 12};
    int field_width = 25;
    int start_x = 5;

    double *vals[] = {&win->x1, &win->y1, &win->x2, &win->y2};

    for (int i = 0; i < 4; i++) {
        InputField *f = &win->fields[i];
        f->buffer[0] = '0';
        f->buffer[1] = '\0';
        f->value = vals[i];

        f->win = derwin(win->overlay, 1, field_width, ys[i], start_x);
        wbkgd(f->win, COLOR_PAIR(2));
    }

    win->result_win = derwin(win->overlay, 1, 30, 14, maxx/2-15);
    wbkgd(win->result_win, COLOR_PAIR(2));

    win->x1 = win->y1 = win->x2 = win->y2 = 0.0;
    win->mode = 0;
    win->active_field = 0;
    update_result(win);
}

void run_interface(curw *win) {
    curs_set(1);
    int ch;
    while (1) {
        ch = wgetch(win->overlay);
        if (ch == 'q' || ch == 'Q' || ch == 27) break;

        // Переключение режима стрелками, переключение между полями ввода
        if (ch == KEY_LEFT || ch == KEY_RIGHT) {
            if (ch == KEY_LEFT){win->mode = 0;}
            else{win->mode = 1;}
            draw_mode_line(win);
            update_result(win);
            draw_result(win);
            wrefresh(win->overlay);
            continue;
        }

        if (ch == KEY_UP || ch == KEY_DOWN) {
            if (ch == KEY_UP) {
                win->active_field = (win->active_field - 1 + 4) % 4;
            } else {
                win->active_field = (win->active_field + 1) % 4;
            }
            draw_fields(win);
            continue;
        }

        if (win->active_field >= 0 && win->active_field < 4) {
            InputField *f = &win->fields[win->active_field];
            int changed = 0;

            if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
                int len = strlen(f->buffer);
                if (len > 1) {
                    f->buffer[len - 1] = '\0';
                    changed = 1;
                }//если ниче не введено то у нас 0 по умолчанию
                else if (len==1){
                    f->buffer[0] = '0';
                    f->buffer[1] = '\0';
                    changed = 1;
                }
            } else if (isdigit(ch) || ch == '.' || ch == '-') {
                int len = strlen(f->buffer);
                if (len == 1 && f->buffer[0] == '0' && ch != '.') {
                    f->buffer[0] = ch;
                    f->buffer[1] = '\0';
                } else {
                    if (len < (int)sizeof(f->buffer) - 1) {
                        f->buffer[len] = ch;
                        f->buffer[len + 1] = '\0';
                    }
                }
                changed = 1;
            }

            if (changed) {
                double val;
                if (is_valid_number(f->buffer, &val)) {
                    *(f->value) = val;
                } else {
                    if (strlen(f->buffer) == 0) {
                        *(f->value) = 0.0;
                        f->buffer[0] = '0';
                        f->buffer[1] = '\0';
                    }
                }
                update_result(win);
                draw_fields(win);
                draw_result(win);
                wrefresh(win->overlay);
            }
        }
    }
    curs_set(0);
}

void cleanup_interface(curw *win) {
    if (win) {
        for (int i = 0; i < 4; i++) {
            if (win->fields[i].win) delwin(win->fields[i].win);
        }
        if (win->result_win) delwin(win->result_win);
        if (win->overlay) delwin(win->overlay);
        if (win->background) delwin(win->background);
        free(win);
    }
    endwin();
}

isdigit(char ch){
    return ((ch-'0')<10);
}

static double fabs(double a){
    if (a<0){return -a;}
    return a;
}