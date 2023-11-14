#include <curses.h>
#include <dirent.h> 

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

#include "files.h"

#define KEY_ESCAPE 27

/*TODO:
IMPLEMENT PROPPER ERROR HANDLING*/

void render(int *cursory, int *cursory_min, int *cursory_max, char *path, int ch) {
    StringList list = list_filenames(path);

    int list_num = *cursory - *cursory_min;

    switch(ch)
    {
        case KEY_ESCAPE: {
            break;
        }
        
        case 10: {
            strcat(path, "/");
            strcat(path, list.list[list_num]);

            if (realpath(path, path) == NULL) {
                exit(1);
            }
            break;
        }

        case KEY_UP: {
            if(*cursory > *cursory_min) {
                (*cursory)--;
            }
            break;
        }
        
        case KEY_DOWN: {
            if(*cursory + 1 < *cursory_max) {
                (*cursory)++;
            }                
            break;
        }
        default: {
            break;
        }
    }

    erase();
    mvprintw(0, 0, "[%s]", path) ;
    for(int printy = *cursory_min; printy < *cursory_max; printy++){
            if((size_t)(printy - *cursory_min) < list.len) {
                mvprintw(printy, 0, "%s", list.list[printy - *cursory_min]);
            } else {
                mvprintw(printy, 0, "~");
            }
    }
    free_list(&list);
    refresh();
    move(*cursory, 0);
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

    char path[PATH_MAX] = ".";

    char actualpath[PATH_MAX];

    realpath(path, actualpath);

    int ch = 0;

    while(loop)
    {
        cursory_max = getmaxy(stdscr);


        render(&cursory, &cursory_min, &cursory_max, actualpath, ch);
        ch = getch();
    }
    endwin();
    return 0;
}

