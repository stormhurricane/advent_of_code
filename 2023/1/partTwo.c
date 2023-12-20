#include <stdio.h>
#include <ctype.h>
#include <string.h>

int findCalibrationValue(char[]);
int mapWordToNumber(const char*);

int main() {
    FILE *file;
    char filename[] = "input.txt";

   
    // Open the file in read mode
    file = fopen(filename, "r");

    // Check if the file is successfully opened
    if (file == NULL) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return 1;  // Return an error code
    }

    // Read and print the contents of the file
    char buffer[64];
    int sumOfAllCalibrationValues = 0;
    int line = 1;


    while (fgets(buffer, sizeof(buffer), file) != NULL) {      
        int value = findCalibrationValue(buffer);
        sumOfAllCalibrationValues += value;

        printf("Calibration value at l. %d: %d\n", line, value);
        line++;
    }

    // Close the file
    fclose(file);

    printf("Sum of all calibration values: %d\n", sumOfAllCalibrationValues);

    return 0; // return success
}

int findCalibrationValue(char buffer[]) {
    // Find the first and last one-digit numbers in the line
    int firstDigit = -1;
    int lastDigit = -1;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (isdigit(buffer[i])) {
            if (firstDigit == -1) {
                firstDigit = buffer[i] - '0';
            }
            lastDigit = buffer[i] - '0';
        }   else if (isalpha(buffer[i])) {
            char word[64];
            int wordValue = -1;   
        
            for (int j = 3; j <=5 && wordValue <= 0; j++) {
                strcpy(word, buffer+i);
                word[j] = '\0';
                wordValue = mapWordToNumber(word);
               
            }
            if (wordValue > 0) {
                if (firstDigit == -1) {
                    firstDigit = wordValue;
                }
                lastDigit = wordValue;
            }
            word[0]= '\0';
        } 
    }

    // Combine the first and last one-digit numbers into a two-digit number
    if (firstDigit != -1 && lastDigit != -1) {
        int twoDigitNumber = firstDigit * 10 + lastDigit;
        return twoDigitNumber;
    }
    return 0;
}

int mapWordToNumber(const char* word) {
    const char* words[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (int i = 0; i < 10; i++) {
        if (strcmp(word, words[i]) == 0) {
            return i;
        }
    }

    return -1;  // Not a recognized word
}