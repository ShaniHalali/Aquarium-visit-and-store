#include "generalFunctions.h"


void printArr(const void** arr, int size, void (*print)(const void*)) {
    if (size == 0) {
        printf("Nothing to display...\n");
    }
    for (int i = 0; i < size; i++) {
        print(arr[i]);
    }
}

void freeArr(void** arr, int size, void (*freeElement)(void*)) {
    for (int i = 0; i < size; i++) {
        freeElement(arr[i]);
    }
    free(arr);  // Free the array itself after freeing its elements
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}

int getValidAge() {
    int age;
    do {
        printf("Enter the age (minimum 1): ");
        scanf("%d", &age);
        if (age >= 1) {
            break;
        }
        printf("Invalid age. Age must be at least 1.\n");
    } while (1);
    return age;
}

int getValidLifeSpan(int age) {
    int lifeSpan;
    do {
        printf("Enter the lifespan (must be greater than age): ");
        scanf("%d", &lifeSpan);
        if (lifeSpan > age) {
            break;
        }
        printf("Invalid lifespan. Lifespan must be greater than age.\n");
    } while (1);
    return lifeSpan;
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
        return 0.0;
    }

    char buffer[sizeof(double)];
    fread(buffer, sizeof(char), sizeof(double), file);

    double value;
    memcpy(&value, buffer, sizeof(double));
    return value;
}
