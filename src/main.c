#include "interface.h"
#include <stdio.h>

int main() {
    if (start_to_work()) {
        fprintf(stderr, "Error initializing curses\n");
        return 1;
    }

    curw *main_win = create_main_win();
    if (!main_win) {
        endwin();
        return 1;
    }

    run_interface(main_win);

    cleanup_interface(main_win);
    return 0;
}