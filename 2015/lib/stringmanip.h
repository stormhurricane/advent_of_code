#ifndef STRINGMANIP_H
#define STRINGMANIP_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

typedef intptr_t ssize_t;

// iterate over file and set line into lineptr
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);
// replaces char *rep with char *with in char *str, n times
// RETURNS -> new char*
char* strReplaceNStr(char* str, char* rep, char* with, int8_t n);
// replace all occurences of char *rep with char *with in char* str
// RETURNS new char*
char* strReplaceStr(char* str, char* rep, char* with);



#endif //STRINGMANIP_H