#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define strcasecmp _stricmp
#include "Shark.h"
#include "generalFunctions.h"

// Function to initialize a single shark
void getSharkFromUser(Shark* shark) {
    printf("Enter shark's name: ");
    scanf("%s", shark->name);

    printf("Enter shark's weight: ");
    scanf("%lf", &shark->weight);
    getSeaCreatureFromUser(&(shark->seaCreature));
}
/*
void printShark(const void* ptr) {
    const Shark* shark = (const Shark*)ptr;
    printf("\nShark: %s\n", shark->name);
    printf("Shark's weight: %.2lf\n", shark->weight);
    printf("Shark's age: %d\n", shark->seaCreature.age);
    printf("Shark's life span: %d\n", shark->seaCreature.lifeSpan);
    printf("Shark's colours: %s, %s\n", SeaCreatureColour[shark->seaCreature.colour1], SeaCreatureColour[shark->seaCreature.colour2]);
    printf("\n");
}
*/

// Function to compare two sharks by name
int compareSharksName(const void* a, const void* b) {
    const Shark* shark1 = *(const Shark**)a;
    const Shark* shark2 = *(const Shark**)b;
    return _stricmp(shark1->name, shark2->name);
}

// Function to compare two sharks by age
int compareSharksAge(const void* a, const void* b) {
    const Shark* shark1 = *(const Shark**)a;
    const Shark* shark2 = *(const Shark**)b;

    if (shark1->seaCreature.age < shark2->seaCreature.age) return -1;
    else if (shark1->seaCreature.age > shark2->seaCreature.age) return 1;
    else return 0;
}

// Function to compare two sharks by weight
int compareSharksWeight(const void* a, const void* b) {
    const Shark* shark1 = *(const Shark**)a;
    const Shark* shark2 = *(const Shark**)b;

    if (shark1->weight < shark2->weight) return -1;
    else if (shark1->weight > shark2->weight) return 1;
    else return 0;
}

Shark* createShark(const char* name, double weight, int age, int lifeSpan, eSeaCreatureColour color1, eSeaCreatureColour color2) {
    Shark* result = (Shark*)calloc(1, sizeof(Shark));
    strncpy(result->name, name, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';
    result->weight = weight;
    result->seaCreature.age = age;
    result->seaCreature.lifeSpan = lifeSpan;
    result->seaCreature.colour1 = color1;
    result->seaCreature.colour2 = color2;
    return result;
}

void writeSharkToFile(Shark* shark, FILE* file) {

    fprintf(file, "%d,%d,%d,%d,%s,%.2f\n", shark->seaCreature.age, shark->seaCreature.lifeSpan, shark->seaCreature.colour1, shark->seaCreature.colour2, shark->name, shark->weight);
}

Shark* readSharkFromFile(FILE* file) {

    Shark* shark = (Shark*)calloc(1, sizeof(Shark));
    if (shark == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    if (fscanf(file, "%d,%d,%d,%d,%49[^,],%lf\n", &shark->seaCreature.age, &shark->seaCreature.lifeSpan, (int*)&shark->seaCreature.colour1, (int*)&shark->seaCreature.colour2, shark->name, &shark->weight) != 6) {
        printf("Error reading from file\n");
        free(shark);
        return NULL;
    }
    return shark;
}
void writeSharkToBinaryFile(Shark* shark, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    // Write the Shark structure to the file
    fwrite(&shark->seaCreature.age, sizeof(int), 1, file);
    fwrite(&shark->seaCreature.lifeSpan, sizeof(int), 1, file);
    fwrite(&shark->seaCreature.colour1, sizeof(int), 1, file);
    fwrite(&shark->seaCreature.colour2, sizeof(int), 1, file);
    int nameLength = strlen(shark->name);
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(shark->name, sizeof(char), nameLength, file);
    writeDoubleToBinaryFile(shark->weight, file);

}

Shark* readSharkFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    Shark* shark = (Shark*)calloc(1, sizeof(Shark));
    if (shark == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    fread(&shark->seaCreature.age, sizeof(int), 1, file);
    fread(&shark->seaCreature.lifeSpan, sizeof(int), 1, file);
    fread(&shark->seaCreature.colour1, sizeof(int), 1, file);
    fread(&shark->seaCreature.colour2, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fread(shark->name, sizeof(char), nameLength, file);
    shark->name[nameLength] = '\0';
    shark->weight = readDoubleFromBinaryFile(file);

    return shark;
}