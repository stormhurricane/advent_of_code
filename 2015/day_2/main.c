#include <stdio.h>
#include <string.h>
#include "line.h"

int main() {
    // open file, and verify it exists
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("No file found");
        return 1;
    }
    
    int totalSqftOfWrappingPaper = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char buffer[5];
    int surfaceAreas[3];

    // read input line by line
    while ((read = getLine(&line, &len, fp)) != -1 ) {
        int length = 0;
        int width = 0;
        int height = 0;
        int previousX = 0;
        int lineLength = (int) strlen(line);
        // iterate over each line
        for (int i = 0; i < lineLength; i++) {
            // split line into single parts
            if (line[i] == 'x') {   
                strncpy(buffer, line + previousX, i);
                previousX = i+1;
                if (!length) {
                    length = atoi(buffer);
                }
                else {
                    width = atoi(buffer);
                }
            }

            if (length && width) {
                strncpy(buffer, line + previousX, lineLength);
                height = atoi(buffer);
                break;
            }
        }

        surfaceAreas[0] = 2 * length * width;
        surfaceAreas[1] = 2 * length * height;
        surfaceAreas[2] = 2 * width * height;
        int minValue = -1;
        int sqftOfWrappingPaper = 0;

        for (unsigned int i =0; i < (sizeof(surfaceAreas)/ sizeof(surfaceAreas[0])); i++ ) {
            if (surfaceAreas[i] < minValue || minValue < 0) {
                minValue = surfaceAreas[i];
            }
            sqftOfWrappingPaper += surfaceAreas[i];
        }
        minValue = minValue / 2;

        sqftOfWrappingPaper += minValue;
        totalSqftOfWrappingPaper += sqftOfWrappingPaper;

        // Hallelujah for emptying buffers...
        memset(buffer,0,strlen(buffer));
    }

    printf("The elves need %d square feet of wrapping paper\n", totalSqftOfWrappingPaper);

    fclose(fp);
    free(line);

    return 0;
}