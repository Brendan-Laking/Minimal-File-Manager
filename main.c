#include <curses.h>
#include <stdbool.h>

#define KEY_ESCAPE 27

void render(int cursory, int cursory_min, int cursory_max) {
    erase();
    mvprintw(0, 0, "THIS IS THE TOP BAR");
    for(int printy = cursory_min; printy < cursory_max; printy++){
        mvprintw(printy, 0, "%d", cursory);
    }
    move(cursory, 0);
    refresh();
}

int main() {
    initscr();
    cbreak();
    noecho();

    keypad(stdscr, true);

    
    int cursory_min = 2;
    int cursory = cursory_min;
    int cursory_max = getmaxy(stdscr);

    bool loop = true;


    while(loop)
    {
        cursory_max = getmaxy(stdscr);
        render(cursory, cursory_min, cursory_max);
        int ch = getch();
        switch(ch)
        {
            case KEY_ESCAPE: {
                loop = false;
                break;
            }
            case KEY_UP: {
                if(cursory > cursory_min) {
                    cursory--;
                }
                break;
            }
            case KEY_DOWN: {
                if(cursory + 1 <  cursory_max) {
                    cursory++;
                }                
                break;
            }
            default: {
                break;
            }
        }
    }
    endwin();
    return 0;
}

