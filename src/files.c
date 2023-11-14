#include "files.h"

void append_string(StringList *list, char *ch) {
    list->list[list->len++] = ch;

    if (list->len >= list->cap) {
        while (list->len >= list->cap) {
            list->cap *= 2;
        }

        char** new_list = realloc(list->list, list->cap * sizeof(*list->list));

        if (new_list == NULL) {
            free(list->list);
            exit(1);
        }

        list->list = new_list;
    }
}

StringList new_list(size_t cap){
    StringList list;
    list.len = 0;
    list.cap = cap;
    list.list = malloc(list.cap * sizeof(*list.list));
    if(list.list == NULL) {
        exit(1);
    }

    return list;
}

StringList list_filenames(char *path) {
    StringList list = new_list(STARTING_CAP);

    DIR *srcdir = opendir(path);

    struct dirent *dir;

    if (srcdir == NULL) {
        exit(1);
    }

    while((dir = readdir(srcdir)) != NULL) {
        append_string(&list, strdup(dir->d_name));
    } 
    closedir(srcdir);
    return list;
}

void free_list(StringList *list) {
    for(size_t i = 0; i < list->len; i++) {
        free(list->list[i]);
    }
    free(list->list);
}