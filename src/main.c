#include "interface.h"

int main() {
    // Инициализация
    start_to_work();

    // Создаём окно
    curw *mywin = make_new_win();
    if (!mywin) {
        endwin();
        printf("Не удалось создать окно\n");
        return 0;
    }

    // Пишем что-нибудь во внутреннюю область (overlay)
    mvwaddstr(mywin->overlay, 1, 1, "Привет, мир!");
    mvwaddstr(mywin->overlay, 2, 1, "Это тестовая строка.");
    wrefresh(mywin->overlay);
    getch();
    // Ждём нажатия клавиши для выхода
    mvaddstr(0, 0, "Нажмите любую клавишу для выхода...");
    refresh();
    
    getch();

    // Завершаем работу
    endwin();
    return 0;
}