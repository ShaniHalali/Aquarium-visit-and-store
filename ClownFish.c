#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClownFish.h"
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define CALCULATE_FOOD_AMOUNT(age) (2.3 * (age))
// Function to initialize a single clown fish
void initClownFish(ClownFish* clownFish) {
    printf("Enter clown fish's name: ");
    scanf("%s", clownFish->name);
    getSeaCreatureFromUser(&(clownFish->seaCreature));
}

/*
// Function to print a single clown fish
void printClownFish(const ClownFish* clownFish) {
    printf("\nClown Fish: %s\n", clownFish->name);
    printf("Clown Fish's food amount: %.2lf\n", CALCULATE_FOOD_AMOUNT(clownFish->seaCreature.age));
    printf("Clown Fish's age: %d\n", clownFish->seaCreature.age);
    printf("Clown Fish's life span: %d\n", clownFish->seaCreature.lifeSpan);
    printf("Clown Fish's colours: %s, %s\n", SeaCreatureColour[clownFish->seaCreature.colour1], SeaCreatureColour[clownFish->seaCreature.colour2]);
    printf("\n");
}
*/


ClownFish* createClownFish(const char* name, int age, int lifeSpan, eSeaCreatureColour color1, eSeaCreatureColour color2) {
    ClownFish* result = (ClownFish*)calloc(1, sizeof(ClownFish));
    strncpy(result->name, name, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';
    result->seaCreature.age = age;
    result->seaCreature.lifeSpan = lifeSpan;
    result->seaCreature.colour1 = color1;
    result->seaCreature.colour2 = color2;
    return result;
}


void writeClownFishToFile(ClownFish* fish, FILE* file) {

    fprintf(file, "%d,%d,%d,%d,%s\n", fish->seaCreature.age, fish->seaCreature.lifeSpan, fish->seaCreature.colour1, fish->seaCreature.colour2, fish->name);
}

ClownFish* readClownFishFromFile(FILE* file) {

    ClownFish* clownFish = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (clownFish == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    if (fscanf(file, "%d,%d,%d,%d,%49[^,]\n", &clownFish->seaCreature.age, &clownFish->seaCreature.lifeSpan, (int*)&clownFish->seaCreature.colour1, (int*)&clownFish->seaCreature.colour2, clownFish->name) != 5) {

    }
    return clownFish;
}
void writeClownFishToBinaryFile(ClownFish* fish, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    fwrite(&fish->seaCreature.age, sizeof(int), 1, file);
    fwrite(&fish->seaCreature.lifeSpan, sizeof(int), 1, file);
    fwrite(&fish->seaCreature.colour1, sizeof(int), 1, file);
    fwrite(&fish->seaCreature.colour2, sizeof(int), 1, file);
    int nameLength = strlen(fish->name);
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(fish->name, sizeof(char), nameLength, file);
}


ClownFish* readClownFishFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    ClownFish* fish = malloc(sizeof(ClownFish));
    if (fish == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Read the ClownFish structure from the file
    fread(&fish->seaCreature.age, sizeof(int), 1, file);
    fread(&fish->seaCreature.lifeSpan, sizeof(int), 1, file);
    fread(&fish->seaCreature.colour1, sizeof(int), 1, file);
    fread(&fish->seaCreature.colour2, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fread(fish->name, sizeof(char), nameLength, file);
    fish->name[nameLength] = '\0'; // Null-terminate the string

    return fish;
}

