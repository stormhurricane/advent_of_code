#include <stdio.h>
#include <ctype.h>

int findCalibrationValue(char[]);

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
    char buffer[256];
    int sumOfAllCalibrationValues = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        sumOfAllCalibrationValues += findCalibrationValue(buffer);
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
        }
    }

    // Combine the first and last one-digit numbers into a two-digit number
    if (firstDigit != -1 && lastDigit != -1) {
        int twoDigitNumber = firstDigit * 10 + lastDigit;
        return twoDigitNumber;
    }
    return 0;
}