#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "line.h"

typedef struct grid{
    int values[1000][1000];
}grid;

grid* createArray() {
    grid *newArray = malloc(sizeof(grid));

    for (int i=0; i < 1000; i++) {
        for (int j=0; j < 1000; j++) {
            newArray->values[i][j] = 0;
        }
    }

    return newArray;
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("No File found!\n");
        return 1;
    }

    clock_t start_time = clock();

    grid* onGrid = createArray();
    grid* brightnessGrid = createArray();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char *whiteSpacePtr;
    char * commaPtr;
    char buffer[4];

    int onLights = 0;
    int brightness = 0;

    while ((read = getLine(&line, &len, fp)) != -1 ) {
        // get the command
        whiteSpacePtr = strchr(line, ' ');
        int length = whiteSpacePtr - line;

        // -1 turn off
        // 1 turn on
        // 2 toggle
        int command = 0;

        if (length == 4) {
            whiteSpacePtr = strchr(whiteSpacePtr + 1, ' ');
            length = whiteSpacePtr - line;
            if (length == 8) {
                command = -1;
            }
            else {
                command = 1;
            }
        }
        else { 
            command = 2;
        }
        
        // use incremental whitespace search to identify the 
        // integers for next part
        commaPtr = strchr(line, ',');

        strncpy(buffer, whiteSpacePtr, commaPtr - whiteSpacePtr);
        int x1 = atoi(buffer);
       
        memset(buffer, 0, strlen(buffer));
        whiteSpacePtr = strchr(commaPtr, ' ');
        strncpy(buffer, commaPtr + 1, whiteSpacePtr - commaPtr);
        int y1 = atoi(buffer);

        memset(buffer, 0, strlen(buffer));
        commaPtr = strrchr(line, ',');
        strncpy(buffer, commaPtr +1, strlen(commaPtr+1));
        int y2 = atoi(buffer);

        memset(buffer, 0, strlen(buffer));
        whiteSpacePtr = strrchr(line, ' ');
        strncpy(buffer, whiteSpacePtr + 1, commaPtr - whiteSpacePtr - 1);
        int x2 = atoi(buffer);

        memset(buffer,0,strlen(buffer));

        // iterate over necessary parts of grid
        while (x1 <= x2) {
            int j = y1;
            while (j <= y2) {
                switch (command) {
                    case -1:
                        onGrid->values[x1][j] = 0;
                        int currentValue = brightnessGrid->values[x1][j];
                        brightnessGrid->values[x1][j] = (currentValue > 0) ? (--currentValue) : 0;
                        break;
                    case 1:
                        onGrid->values[x1][j] = 1;
                        brightnessGrid->values[x1][j] +=1;
                        break;
                    case 2: 
                        onGrid->values[x1][j] = (onGrid->values[x1][j] == 0) ? 1 : 0;
                        brightnessGrid->values[x1][j] += 2;
                        break;
                    default:
                        break;
                }
                j++;
            }
            x1++;
        }
    }

    // iterate over whole grid and count
    for (int i=0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            onLights += onGrid->values[i][j];
            brightness += brightnessGrid->values[i][j];
        }
    }

    clock_t end_time = clock();

    free(fp);
    free(line);
    free(whiteSpacePtr);
    free(commaPtr);
    free(onGrid);
    free(brightnessGrid);

    printf("%d lights are on according to santas plan\n", onLights);
    printf("%d is the brightness according to santas plan", brightness);

    float seconds = (float)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}