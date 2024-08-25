#include <stdio.h>
#include "SeaCreatures.h"
#include <stdlib.h>

eSeaCreatureColour getColourFromUser()
{
    int i, c;
    printf("Colour options:\n");
    do {
        for (i = 0; i < eNofSeaCreatureColours; i++)
            printf("Enter %d for %s\n", i, SeaCreatureColour[i]);
        scanf("%d", &c);
    } while (c < 0 || c >= eNofSeaCreatureColours);
    return (eSeaCreatureColour)c;
}

void getColoursForSeaCreature(SeaCreature* pPer) {
    printf("Please enter the first colour:\n");
    pPer->colour1 = getColourFromUser();

    printf("Please enter the second colour:\n");
    pPer->colour2 = getColourFromUser();
}

void getSeaCreatureFromUser(SeaCreature* pPer) {
    printf("Please enter the age: \n");
    scanf("%d", &pPer->age);
    printf("Please enter the life span: \n");
    scanf("%d", &pPer->lifeSpan);
    getColoursForSeaCreature(pPer);
}
/*
void printSeaCreature(const SeaCreature* pPer) {
    printf("Age %d\t Life span %d\t Colour 1: %s\t Colour 2: %s\n",
        pPer->age, pPer->lifeSpan, SeaCreatureColour[pPer->colour1], SeaCreatureColour[pPer->colour2]);
}
*/

SeaCreature* createSeaCreature(int age, int lifeSpan, eSeaCreatureColour color1, eSeaCreatureColour color2) {
    SeaCreature* result = (SeaCreature*)calloc(1, sizeof(SeaCreature));
    result->age = age;
    result->lifeSpan = lifeSpan;
    result->colour1 = color1;
    result->colour2 = color2;
    return result;
}
void writeSeaCreatureToFile(SeaCreature* seaCreature, FILE* file) {
    if (seaCreature == NULL || file == NULL) {
        printf("Invalid input parameters!\n");
        return;
    }
    fprintf(file, "%d,%d,%d,%d\n", seaCreature->age, seaCreature->lifeSpan, seaCreature->colour1, seaCreature->colour2);
}

SeaCreature* readSeaCreatureFromFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    SeaCreature* seaCreature = (SeaCreature*)calloc(1, sizeof(SeaCreature));
    if (seaCreature == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (fscanf(file, "%d,%d,%d,%d ", &seaCreature->age, &seaCreature->lifeSpan, &seaCreature->colour1, &seaCreature->colour2) != 4) {
        printf("Failed to read SeaCreature details from file!\n");
        free(seaCreature);
        return NULL;
    }

    return seaCreature;
}
void writeSeaCreatureToBinFile(SeaCreature* seaCreature, FILE* file) {
    if (seaCreature == NULL || file == NULL) {
        printf("Invalid input parameters!\n");
        return;
    }

    fwrite(&seaCreature->age, sizeof(int), 1, file);
    fwrite(&seaCreature->lifeSpan, sizeof(int), 1, file);
    fwrite(&seaCreature->colour1, sizeof(eSeaCreatureColour), 1, file);
    fwrite(&seaCreature->colour2, sizeof(eSeaCreatureColour), 1, file);
}

SeaCreature* readSeaCreatureFromBinFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    SeaCreature* seaCreature = (SeaCreature*)calloc(1, sizeof(SeaCreature));
    if (seaCreature == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    if (fread(&seaCreature->age, sizeof(int), 1, file) != 1 ||
        fread(&seaCreature->lifeSpan, sizeof(int), 1, file) != 1 ||
        fread(&seaCreature->colour1, sizeof(eSeaCreatureColour), 1, file) != 1 ||
        fread(&seaCreature->colour2, sizeof(eSeaCreatureColour), 1, file) != 1) {
        printf("Failed to read SeaCreature details from file!\n");
        free(seaCreature);
        return NULL;
    }

    return seaCreature;
}