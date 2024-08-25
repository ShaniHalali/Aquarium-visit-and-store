#include "ChildFish.h"
#include <string.h>
#include <stdio.h>


void printChildFish(ChildFish* child)
{
    PRINTCHILD(child);
}



void writeFreshFishToTxtFile(FreshFish* fish, FILE* file) {
    fprintf(file, "%d,%d,%s\n", fish->age, fish->lifeSpan, fish->name);
}

void writeFreshFishToBinaryFile(FreshFish* fish, FILE* file) {
    fwrite(&fish->age, sizeof(int), 1, file);
    fwrite(&fish->lifeSpan, sizeof(int), 1, file);
    int nameLength = strlen(fish->name);
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(fish->name, sizeof(char), nameLength, file);
}

FreshFish* readFreshFishFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    FreshFish* fish = malloc(sizeof(FreshFish));
    if (fish == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Read the data from the file
    fread(&fish->age, sizeof(int), 1, file);
    fread(&fish->lifeSpan, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fish->name = malloc((nameLength + 1) * sizeof(char)); // Allocate memory for name (+1 for null terminator)
    if (fish->name == NULL) {
        printf("Memory allocation failed!\n");
        free(fish); // Clean up allocated memory before returning NULL
        return NULL;
    }
    fread(fish->name, sizeof(char), nameLength, file);
    fish->name[nameLength] = '\0'; // Null-terminate the string

    return fish;
}

void writeChildFishToBinaryFile(ChildFish* child, FILE* fp) {
    fwrite(&child->fishNumber, sizeof(int), 1, fp);
}

ChildFish* readChildFishFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    ChildFish* child = malloc(sizeof(ChildFish));
    if (child == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    fread(&child->fishNumber, sizeof(int), 1, file);

    return child;
}

void writeChildFishToTxtFile(ChildFish* child, FILE* fp) {
    fprintf(fp, "%d\n", child->fishNumber);
}

FreshFish* readFreshFishFromFile(FILE* fp) {
    FreshFish* fish = (FreshFish*)calloc(1, sizeof(FreshFish));
    fish->name = (char*)calloc(100, sizeof(char));
    if (fscanf(fp, "%d,%d,%s\n", &fish->age, &fish->lifeSpan, fish->name) != 3) {
        return NULL;
    }
    return fish;
}


FreshFish* createFreshFish(int age, int lifeSpan, char* name) {
    FreshFish* result = (FreshFish*)calloc(1, sizeof(FreshFish));
    result->age = age;
    result->lifeSpan = lifeSpan;
    result->name = name;
    return result;
}


ChildFish* createChildFIsh(int fishNumber, FreshFish* firstParent, FreshFish* secondParent) {
    ChildFish* result = (ChildFish*)calloc(1, sizeof(ChildFish));
    result->parentsNames = (char*)malloc(strlen(firstParent->name) + strlen(secondParent->name) + 2);
    strcpy(result->parentsNames, firstParent->name);
    strcat(result->parentsNames, "_");
    strcat(result->parentsNames, secondParent->name);
    result->fishNumber = fishNumber;
    result->firstParent = firstParent;
    result->secondParent = secondParent;
    firstParent->child = result;
    secondParent->child = result;
    return result;
}


FreshFish* createFreshFishFromUser() {
    int age = 0;
    printf("\nEnter age: ");
    scanf("%d", &age);

    int lifeSpan = 0;
    do {
        printf("\nEnter life span age bigger than %d: ", age);
        scanf("%d", &lifeSpan);
    } while (lifeSpan <= age);


    char name[MAX_ITEMS];
    printf("\nEnter name: ");
    scanf("%s", name);
    return createFreshFish(age, lifeSpan, name);
}