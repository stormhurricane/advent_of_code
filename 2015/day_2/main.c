#include <stdio.h>
#include <string.h>
#include <time.h>
#include "line.h"

int main() {
    // open file, and verify it exists
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("No file found");
        return 1;
    }
    
    clock_t start = clock();

    int totalSqftOfWrappingPaper = 0;
    int totalFeetOfRibbon = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char buffer[5];
    int surfaceAreas[] = {0, 0, 0};
    // w x l x h
    int values[] = {0, 0, 0};

    // read input line by line
    while ((read = getLine(&line, &len, fp)) != -1 ) {
        values[0] = 0;
        values[1] = 0;
        values[2] = 0;
        int previousX = 0;
        int lineLength = (int) strlen(line);
        // iterate over each line
        for (int i = 0; i < lineLength; i++) {
            // split line into single parts
            if (line[i] == 'x') {
                strncpy(buffer, line + previousX, i);
                previousX = i+1;
                if (!values[0]) {
                    values[0] = atoi(buffer);
                }
                else {
                    values[1] = atoi(buffer);
                }
            }

            if (values[0] && values[1]) {
                strncpy(buffer, line + previousX, lineLength);
                values[2] = atoi(buffer);
                break;
            }
        }

        // insertion sort algorithm, cause why not
        for (unsigned int i =1; i < (sizeof(values)/ sizeof(values[0])); i++ ) {
            int tmp = values[i];
            int j = i -1;
            while (j >= 0 && values[j] > tmp) {
                values[j+1] = values[j];
                j = j-1;
            }
            values[j+1] = tmp;
        }

        // formulas come from the description
        surfaceAreas[0] = 2 * values[0] * values[1];
        surfaceAreas[1] = 2 * values[0] * values[2];
        surfaceAreas[2] = 2 * values[1] * values[2];

        int minValue = -1;
        int sqftOfWrappingPaper = 0;
        int feetOfRibbon = 0;

        // find the minimal value as "slack"
        for (unsigned int i =0; i < 3; i++ ) {
            if (surfaceAreas[i] < minValue || minValue < 0) {
                minValue = surfaceAreas[i];
            }
            sqftOfWrappingPaper += surfaceAreas[i];
        }
        minValue = minValue / 2;

        sqftOfWrappingPaper += minValue;

        feetOfRibbon = 2 * values[0] + 2 * values[1] + (values[0] * values[1] * values[2]);

        totalSqftOfWrappingPaper += sqftOfWrappingPaper;
        totalFeetOfRibbon += feetOfRibbon;

        // Hallelujah for emptying buffers...
        memset(buffer,0,strlen(buffer));
    }

    clock_t end = clock();

    fclose(fp);
    free(line);

    printf("The elves need %d square feet of wrapping paper\n", totalSqftOfWrappingPaper);
    printf("The elves need %d feet of ribbon\n", totalFeetOfRibbon);
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);

    return 0;
}