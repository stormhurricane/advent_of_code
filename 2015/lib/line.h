#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

typedef intptr_t ssize_t;

ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

#endif //LINE_H