#include <curses.h>
#include <dirent.h> 

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h> 

#define KEY_ESCAPE 27

void render(int cursory, int cursory_min, int cursory_max, char* path) {
    DIR *srcdir = opendir(path);

    struct dirent *dir;

    if (srcdir == NULL) {
        exit(1);
    }

    erase();
    mvprintw(0, 0, "THIS IS THE TOP BAR");
    for(int printy = cursory_min; printy < cursory_max; printy++){
        if((dir = readdir(d)) != NULL) {
            mvprintw(printy, 0, "%s\n", dir->d_name);
        } else {
            mvprintw(printy, 0, ".");
        }
    }
    refresh();
    move(cursory, 0);
    closedir(d);
}

int main() {
    initscr();
    cbreak();
    noecho();

    keypad(stdscr, true);

    if(chdir("~") == 1) {
        return 0;
    } 

    int cursory_min = 2;
    int cursory = cursory_min;
    int cursory_max = getmaxy(stdscr);

    bool loop = true;


    while(loop)
    {
        cursory_max = getmaxy(stdscr);
        render(cursory, cursory_min, cursory_max, ".");
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

