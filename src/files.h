#ifndef FILES_H_
#define FILES_H_

#include <curses.h>
#include <dirent.h> 

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define STARTING_CAP 16

typedef struct StringList {
    char** list;
    size_t cap;
    size_t len;
} StringList;

StringList list_filenames(char *path);

void free_list(StringList *list);

#endif //FILES_H_