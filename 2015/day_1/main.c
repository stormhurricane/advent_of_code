#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    // Open Filepointer
    FILE *fptr = fopen("input.txt", "r");

    // if file not found, pointer is null
    if (!fptr) {
        printf("No File found!");
        return 1;
    }

    clock_t start = clock();

    int floorCount = 0;
    char c;

    int index = 1;
    // standard C has no bool, so I abuse the enteredBasement var to also store the value
    int enteredBasement = 0;

    // check file, char by char
    do {
        c = fgetc(fptr);

        if (c == '(') {
            floorCount ++;
        } else if (c == ')') {
            floorCount --;
            if (floorCount < 0 && !enteredBasement) {
                enteredBasement = index;
            }
        }   
        index ++;
    }
    while (c != EOF);

    clock_t end = clock();

    fclose(fptr);

    printf("Santa got up to the %d floor\n", floorCount);
    printf("Santa entered the basement first at instruction %d", enteredBasement);
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}