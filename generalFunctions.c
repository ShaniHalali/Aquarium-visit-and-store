#include "generalFunctions.h"


void printArr(const void** arr, int size, void (*print)(const void*)) {
    for (int i = 0; i < size; i++) {
        print(arr[i]);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}


// Function to write a double value to a binary file
void writeDoubleToBinaryFile(double value, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    char buffer[sizeof(double)];
    memcpy(buffer, &value, sizeof(double));
    fwrite(buffer, sizeof(char), sizeof(double), file);
}

// Function to read a double value from a binary file
double readDoubleFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return 0.0; // Return a default value or handle error as needed
    }

    char buffer[sizeof(double)];
    fread(buffer, sizeof(char), sizeof(double), file);

    double value;
    memcpy(&value, buffer, sizeof(double));
    return value;
}
