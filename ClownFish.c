#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClownFish.h"

#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define CALCULATE_FOOD_AMOUNT(age) (2.3 * (age))

void getClownFishFromUser(ClownFish* fish) {
    printf("Enter name: ");
    scanf("%49s", fish->name);

    fish->seaCreature.age = getValidAge();

    fish->seaCreature.lifeSpan = getValidLifeSpan(fish->seaCreature.age);

    getValidColours(&fish->seaCreature);
}



ClownFish* createClownFish(const char* name, int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2) {
    ClownFish* result = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (!result) {
        printf("Memory allocation failed for ClownFish.\n");
        return NULL;
    }

    strncpy(result->name, name, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';

    result->seaCreature.age = age;
    result->seaCreature.lifeSpan = lifeSpan;
    result->seaCreature.color1 = color1;
    result->seaCreature.color2 = color2;

    return result;
}

void writeClownFishToFile(ClownFish* fish, FILE* file) {

    fprintf(file, "%s,%d,%d,%d,%d\n",  fish->name,fish->seaCreature.age, fish->seaCreature.lifeSpan, fish->seaCreature.color1, fish->seaCreature.color2);
}

ClownFish* readClownFishFromFile(FILE* file) {

    ClownFish* clownFish = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (clownFish == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    if (fscanf(file, "%49[^,],%d,%d,%d,%d\n",  clownFish->name, &clownFish->seaCreature.age, &clownFish->seaCreature.lifeSpan, (int*)&clownFish->seaCreature.color1, (int*)&clownFish->seaCreature.color2) != 5) {

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
    fwrite(&fish->seaCreature.color1, sizeof(int), 1, file);
    fwrite(&fish->seaCreature.color2, sizeof(int), 1, file);
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
    fread(&fish->seaCreature.color1, sizeof(int), 1, file);
    fread(&fish->seaCreature.color2, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fread(fish->name, sizeof(char), nameLength, file);
    fish->name[nameLength] = '\0';

    return fish;
}

