#include <stdio.h>
#include "SeaCreatures.h"
#include <stdlib.h>




eSeaCreatureColor getValidColour(const char* prompt) {
    int i, c;
    printf("%s\n", prompt);
    do {
        for (i = 0; i < eNofSeaCreatureColors; i++)
            printf("%d - %s\n", i, SeaCreatureColour[i]);
        scanf("%d", &c);
        if (c >= 0 && c < eNofSeaCreatureColors) {
            break;
        }
        printf("Invalid color choice. Please choose a valid color.\n");
    } while (1);
    return (eSeaCreatureColor)c;
}

void getValidColours(SeaCreature* creature) {
    creature->color1 = getValidColour("Please enter the first colour:");

    do {
        creature->color2 = getValidColour("Please enter the second colour:");
        if (creature->color1 != creature->color2) {
            break;
        }
        printf("Invalid colors. The two colors must be different.\n");
    } while (1);
}

SeaCreature* getSeaCreatureFromUser() {
    SeaCreature* newCreature = (SeaCreature*)malloc(sizeof(SeaCreature));
    if (!newCreature) {
        printf("Memory allocation failed for SeaCreature.\n");
        return NULL;
    }
    newCreature->age = getValidAge();
    newCreature->lifeSpan = getValidLifeSpan(newCreature->age);

    getValidColours(newCreature);

    return newCreature;
}
SeaCreature* createSeaCreature(int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2) {
    SeaCreature* result = (SeaCreature*)calloc(1, sizeof(SeaCreature));
    result->age = age;
    result->lifeSpan = lifeSpan;
    result->color1 = color1;
    result->color2 = color2;
    return result;
}

void writeSeaCreatureToFile(SeaCreature* seaCreature, FILE* file) {
    if (seaCreature == NULL || file == NULL) {
        printf("Invalid input parameters!\n");
        return;
    }
    fprintf(file, "%d,%d,%d,%d\n", seaCreature->age, seaCreature->lifeSpan, seaCreature->color1, seaCreature->color2);
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

    if (fscanf(file, "%d,%d,%d,%d ", &seaCreature->age, &seaCreature->lifeSpan, &seaCreature->color1, &seaCreature->color2) != 4) {
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
    fwrite(&seaCreature->color1, sizeof(eSeaCreatureColor), 1, file);
    fwrite(&seaCreature->color2, sizeof(eSeaCreatureColor), 1, file);
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
        fread(&seaCreature->color1, sizeof(eSeaCreatureColor), 1, file) != 1 ||
        fread(&seaCreature->color2, sizeof(eSeaCreatureColor), 1, file) != 1) {
        printf("Failed to read SeaCreature details from file!\n");
        free(seaCreature);
        return NULL;
    }

    return seaCreature;
}
