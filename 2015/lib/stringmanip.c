#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

typedef intptr_t ssize_t;

// https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472
ssize_t getLine(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}


// https://stackoverflow.com/a/779960
char* strReplaceNStr(char* str, char* rep, char* with, int8_t n){
    // sanity checks
    if (n == 0) return str;
    if (!str || !rep || !with) return str;

    if (!(strstr(str, rep))) return str;

    char* newString;
    char* iter;
    char *tmp;
    size_t len_rep = strlen(rep);
    size_t len_with = strlen(with);
    size_t len_front;
    size_t count;

    // otherwise, the free at the end has Undefined behavior
    char* begin = str;

    // count max number of replacements
    iter = str;
    for (count = 0; (tmp = strstr(iter, rep)); count++) {
        iter = tmp + len_rep;
    }

    size_t reps = n < 0 ? count : n;

    // due to this, the newString can replace the given string (being on the heap)
    newString = malloc(strlen(str) + (len_with - len_rep) * reps + 1);

    tmp = newString;
       
    while (count-- && n--) {
        iter = strstr(str, rep);
        len_front = iter - str;

        tmp = strncpy(tmp, str, len_front) + len_front;

        tmp = strcpy(tmp, with) + len_with;

        str += len_front + len_rep;

    }

    strcpy(tmp, str);
    // god save free. or something
    free(begin);
    
    return newString;
}


char* strReplaceStr(char* str, char* rep, char* with){
    return strReplaceNStr(str, rep, with, -1);
}
