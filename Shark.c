#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define strcasecmp _stricmp
#include "Shark.h"
#include "generalFunctions.h"

void getSharkFromUser(Shark* shark) {
    printf("Enter shark name: ");
    scanf("%s", shark->name);

    do {
        printf("Enter shark weight (must be greater than 10): ");
        scanf("%lf", &shark->weight);
        if (shark->weight > 10) {
            break; // Valid input
        }
        printf("Invalid weight. Weight must be greater than 10.\n");
    } while (1);

    shark->seaCreature.age = getValidAge();
    shark->seaCreature.lifeSpan = getValidLifeSpan(shark->seaCreature.age);

    getValidColours(&shark->seaCreature);
}

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

Shark* createShark(const char* name, double weight, int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2) {
    Shark* result = (Shark*)calloc(1, sizeof(Shark));
    strncpy(result->name, name, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';
    result->weight = weight;
    result->seaCreature.age = age;
    result->seaCreature.lifeSpan = lifeSpan;
    result->seaCreature.color1 = color1;
    result->seaCreature.color2 = color2;
    return result;
}

void writeSharkToFile(Shark* shark, FILE* file) {

    fprintf(file, "%s,%d,%d,%d,%d,%.2f\n", shark->name, shark->seaCreature.age, shark->seaCreature.lifeSpan, shark->seaCreature.color1, shark->seaCreature.color2, shark->weight);
}

Shark* readSharkFromFile(FILE* file) {

    Shark* shark = (Shark*)calloc(1, sizeof(Shark));
    if (shark == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    if (fscanf(file, "%d,%d,%d,%d,%49[^,],%lf\n", &shark->seaCreature.age, &shark->seaCreature.lifeSpan, (int*)&shark->seaCreature.color1, (int*)&shark->seaCreature.color2, shark->name, &shark->weight) != 6) {
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
    fwrite(&shark->seaCreature.color1, sizeof(int), 1, file);
    fwrite(&shark->seaCreature.color2, sizeof(int), 1, file);
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
    fread(&shark->seaCreature.color1, sizeof(int), 1, file);
    fread(&shark->seaCreature.color2, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fread(shark->name, sizeof(char), nameLength, file);
    shark->name[nameLength] = '\0';
    shark->weight = readDoubleFromBinaryFile(file);

    return shark;
}
