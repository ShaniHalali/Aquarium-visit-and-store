#ifndef CLOWN_FISH_H
#define CLOWN_FISH_H

#include "SeaCreatures.h"


typedef struct {
    SeaCreature seaCreature;
    char name[50];
} ClownFish;

void initClownFish(ClownFish* clownFish);
void printClownFish(const ClownFish* clownFish);
void writeClownFishToFile(ClownFish* fish, FILE* file);
ClownFish* readClownFishFromFile(FILE* file);
ClownFish* createClownFish(const char* name, int age, int lifeSpan, eSeaCreatureColour color1, eSeaCreatureColour color2);
void writeClownFishToBinaryFile(ClownFish* fish, FILE* file);
ClownFish* readClownFishFromBinaryFile(FILE* file);
#endif
