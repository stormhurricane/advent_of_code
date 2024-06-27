#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "line.h"
#include "map.h"

HashTable *ht;
HashTable *results;

// checks if a string is a complete number
int isnumber(char* str) {
    for (uint8_t i = 0; i< strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

uint16_t calculate(char* name) {
    
    if (isnumber(name)) {
        uint16_t res =  (uint16_t) atoi(name);
        return res;
    }

    void* previousComputed = lookup(results, name);

    if (previousComputed) {
        return *((int*) previousComputed);
    }

    uint16_t result = 0;

    char* instruction = lookup(ht, name);
    // sanity check
    if (!instruction) {
        return 0;
    }

    if (!strchr(instruction, ' ')) {
        result = calculate(instruction);
        
        uint16_t *res = malloc(sizeof(uint16_t));
        *res = result;
        insert(results, name, res);
        return *res;
    }

    if (strncmp(instruction, "NOT", 3) == 0) {
        uint16_t help = calculate(strchr(instruction, ' ') + 1);
        result =  help ^ 0xffff;
        uint16_t *res = malloc(sizeof(uint16_t));
        *res = result;
        insert(results, name, res);
        return *res;
    }

    char *copy = malloc(strlen(instruction));
    strcpy(copy, instruction);

    char *keyword = strchr(copy, ' ') + 1;
    copy[keyword - copy - 1] = '\0';
    char *secondWire = strchr(keyword, ' ') + 1;
    keyword[secondWire - keyword - 1] = '\0'; 
 

    if (strncmp(keyword, "AND", 3) == 0) {
        uint16_t help = calculate(copy);
        uint16_t sec = calculate(secondWire);
        result = help & sec;
    }
    else if (strncmp(keyword, "OR", 2) == 0) {
        uint16_t help = calculate(copy);
        uint16_t sec = calculate(secondWire);
        result = help | sec;
    }
    else if (strncmp(keyword, "RSHIFT", 6) == 0 ){
        uint16_t help = calculate(copy);
        uint16_t sec = calculate(secondWire);
        result = help >> sec;
    }
    else if (strncmp(keyword, "LSHIFT", 6) == 0) {
        uint16_t help = calculate(copy);
        uint16_t sec = calculate(secondWire);
        result = (help << sec);
    }       

    uint16_t *res = malloc(sizeof(uint16_t));
    *res = result;
    insert(results, name, res);
    return result;
}


int main() {
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("No File found!\n");
        return 1;
    }

    clock_t start_time = clock();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char *seperatorPtr;

    ht = createTable();
    results = createTable();

    while ((read = getLine(&line, &len, fp)) != -1 ) {
        seperatorPtr = strchr(line, '-');

        line[seperatorPtr-line-1] = '\0';
        seperatorPtr += 3;
        seperatorPtr[strlen(seperatorPtr) - 1] = '\0';

        char* value = malloc(strlen(line)+1);
        strcpy(value, line);

        insert(ht, seperatorPtr, value);
    }


    uint16_t old_a = calculate("a");
    HashTable *oldResults = results;

//    insert(ht, "b", &old_a);
    // destroyTable(results);
  //  results = createTable();
    uint16_t a = calculate("a");

    free(seperatorPtr);
    free(line);
    free(fp);
    destroyTable(ht);
    destroyTable(results);

    clock_t end_time = clock();

    printf("Old_a: %u", old_a);
    printf("\nNew_a: %u", a);

    float seconds = (float)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}