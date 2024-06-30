#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "line.h"

int8_t isHexadecimalChar(char* str);
size_t countChar(char* str, char ch);
char* replaceCharacters(char* str, char* toReplace, char* replaceWith);
char* replaceNCharacters(char* str, char* toReplace, char* replaceWith, int8_t occurences);

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("File not found!\n");
        return 1;
    }

    clock_t startTime = clock();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char* help;
    char* buffer = malloc(8);
    char* currentStr;

    size_t totalNumberOfCharacters = 0;
    size_t totalNumberOfIntegratedCharacters = 0;
    size_t totalNumberOfStringCharacters = 0;

    while ((read = getLine(&line, &len, fp)) != -1 ) {
        // I like memory management.
        currentStr = malloc(strlen(line) + 1);
        strcpy(currentStr, line);
        help = NULL;
        // setting buffers to 0 ios fun
        memset(buffer,0,strlen(buffer));

        // replace \n
        currentStr[strlen(currentStr) -1 ] = '\0';

        totalNumberOfCharacters += strlen(currentStr);
        totalNumberOfIntegratedCharacters += 2 + strlen(currentStr)
            + countChar(currentStr, '\"')+ countChar(currentStr, '\\');

        // trailing and leading quotation marks
        currentStr += 1;
        currentStr[strlen(currentStr) -1 ] = '\0';


        currentStr = replaceCharacters(currentStr, "\\\"", "\"");

        // fucked up logic
        while ((help = strstr(currentStr, "\\x"))){
            // is this truy hexadecimal?
            if (!isHexadecimalChar(help + 2) || !isHexadecimalChar(help+3) ) {
                currentStr = replaceNCharacters(currentStr, "\\x", "\\a", 1);
                continue;
            }

            // is it a double backslash?
            if ((help - currentStr)) {
                help -= 1;
                if (help[0] == '\\') {
                    if (strstr(currentStr, "\\") == help -1) {
                        currentStr = replaceNCharacters(currentStr, "\\\\", "", 1);
                        strcat(currentStr, "\\\\");
                        continue;
                    }
                }
                else help++;
            }

            strncpy(buffer, help, 4);
            buffer[4] = '\0';
            currentStr = replaceNCharacters(currentStr, buffer, "F", 1);
        }

        currentStr = replaceCharacters(currentStr, "\\\\", "\\");

        totalNumberOfStringCharacters += strlen(currentStr);

        // I like memory management...
        free(currentStr);
    }

    free(buffer);
    free(line);
    free(fp);

    clock_t endTime = clock();

    printf("Integration difference is %u\n", totalNumberOfIntegratedCharacters - totalNumberOfCharacters);
    printf("Eval difference is %u", totalNumberOfCharacters - totalNumberOfStringCharacters);

    float seconds = (float)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}

// https://stackoverflow.com/a/779960
char* replaceNCharacters(char* str, char* toReplace, char* replaceWith, int8_t occurences) {
    // sanity checks
    if (occurences == 0) return str;
    if (!str || !toReplace || !replaceWith) return str;

    if (!(strstr(str, toReplace))) return str;

    char* newString;
    char* iter;
    char *tmp;
    size_t len_rep = strlen(toReplace);
    size_t len_with = strlen(replaceWith);
    size_t len_front;
    size_t count;

    // otherwise, the free at the end has Undefined behavior
    char* begin = str;

    // count max number of replacements
    iter = str;
    for (count = 0; (tmp = strstr(iter, toReplace)); count++) {
        iter = tmp + len_rep;
    }

    size_t reps = occurences < 0 ? count : occurences;

    // due to this, the newString can replace the given string (being on the heap)
    newString = malloc(strlen(str) + (len_with - len_rep) * reps + 1);

    tmp = newString;
       
    while (count-- && occurences--) {
        iter = strstr(str, toReplace);
        len_front = iter - str;

        tmp = strncpy(tmp, str, len_front) + len_front;

        tmp = strcpy(tmp, replaceWith) + len_with;

        str += len_front + len_rep;

    }

    strcpy(tmp, str);
    // god save free. or something
    free(begin);
    
    return newString;
}


char* replaceCharacters(char* str, char* toReplace, char* replaceWith){
    return replaceNCharacters(str, toReplace, replaceWith, -1);
}


int8_t isHexadecimalChar(char* str) {
    return isxdigit(str[0]);
}

size_t countChar(char* str, char ch) {
    size_t count = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    return count;
}