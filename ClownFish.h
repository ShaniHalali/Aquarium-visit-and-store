#ifndef CLOWN_FISH_H
#define CLOWN_FISH_H

#include "SeaCreatures.h"


typedef struct {
    SeaCreature seaCreature;
    char name[50];
} ClownFish;



void getClownFishFromUser(ClownFish* fish);
void writeClownFishToFile(ClownFish* fish, FILE* file);
ClownFish* readClownFishFromFile(FILE* file);
ClownFish* createClownFish(const char* name, int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2);
void writeClownFishToBinaryFile(ClownFish* fish, FILE* file);
ClownFish* readClownFishFromBinaryFile(FILE* file);
#endif
