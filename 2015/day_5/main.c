#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "line.h"

int partOne(char *line) {
    int vowelCounter = 0;
    int hasPair = 0;

    // inspect each char in the line, and chheck the three rules
    // vowelCounter has to be equal or more than 3
    // needs a pair
    // and none of the strings ab, cd, pq, xy
    for (int i = 0; i < strlen(line) - 1; i++ ) {
        switch(line[i]) {
            case 'a':
                if (line[i+1] == 'b') return 0;
                vowelCounter ++;
                break;
            case 'c':
                if (line[i+1] == 'd') return 0;
                break;
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vowelCounter++;
                break;
            case 'p':
                if (line[i+1] == 'q') return 0;
                break;
            case 'x':
                if (line[i+1] == 'y') return 0;
                break;
            default:
                break;
        }

        if (!hasPair && (line[i+1] == line[i])) {
            hasPair = 1;
        }
    }

    return (vowelCounter >= 3) && hasPair;
}

int partTwo(char *line) {
    int ruleOfXyX = 0;
    int ruleOfPair = 0;

    int lineLength = strlen(line);

    // inspects each char one by one, and checks the rules XyX
    // and that a double char pair is existent
    for (int i = 0; i < lineLength; i++ ) {
        if (i+2 < lineLength && !ruleOfXyX) {
            if (line[i] == line[i+2]) {
                ruleOfXyX = 1;
            }
        }
        
        if (!ruleOfPair) {
            int j = i +2;

            for (; j < lineLength - 1; j++) {
                if (line[i] == line[j]) {
                    if (line[i+1] == line[j+1]) {
                        ruleOfPair = 1;
                    }
                }
            }
        }
    }

    return ruleOfXyX && ruleOfPair;
}

int main() {
    // open file, and verify it exists
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("No file found");
        return 1;
    }

    clock_t start = clock();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    int oldNiceCount = 0;
    int newNiceCount = 0;
    while ((read = getLine(&line, &len, fp)) != -1 ) {
        oldNiceCount += partOne(line);
        newNiceCount += partTwo(line);
    }

    clock_t end = clock();

    printf("%d of nice strings in old counting\n", oldNiceCount);
    printf("%d of nice strings in new counting", newNiceCount);
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nNeeded Time: %f seconds", seconds);
}