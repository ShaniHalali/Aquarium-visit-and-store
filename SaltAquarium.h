#ifndef SALT_WATER_AQUARIUM_H
#define SALT_WATER_AQUARIUM_H
#include "Shark.h"
#include "ClownFish.h"
#include "SeaCreatures.h"
#include <stdio.h>

typedef struct {
    SeaCreature** seaCreatures;
    int numSeaCreatures;
    Shark** sharks;
    int numSharks;
    ClownFish** clownFishes;
    int numClownFishes;

} SaltAquarium;

SaltAquarium* initSaltAquarium();
void printAllSaltAquariums(SaltAquarium* aquarium);
void addSeaCreature(SaltAquarium* saltAquarium, SeaCreature* seaCreature);
void printSeaCreature(const void* creature);
void ageAllSeaCreatures(SaltAquarium* aquarium);

void addShark(SaltAquarium* saltAquarium, Shark* shark);
void ageAllSharks(SaltAquarium* aquarium);
void sortSharksMenu(SaltAquarium* aquarium);
void sharkSearchMenu(SaltAquarium* aquarium);
Shark* findSharkByWeight(SaltAquarium* aquarium, double weight);
Shark* findSharkByName(SaltAquarium* aquarium, char* name);
Shark* findSharkByAge(SaltAquarium* aquarium, int age);

void addClownFish(SaltAquarium* saltAquarium, ClownFish* clownFish);
void printClownFish(const ClownFish* clownFish);
void ageAllClownFishes(SaltAquarium* aquarium);

void writeSaltAquariumToTxtFile(SaltAquarium* saltAquarium, FILE* fp);
void writeSaltAquariumToBinaryFile(SaltAquarium* saltAquarium, FILE* fp);
SaltAquarium* readSaltAquariumFromFile(FILE* fp);
SaltAquarium* readSaltAquariumFromBinaryFile(FILE* file);
void freeSaltAquarium(SaltAquarium* aquarium);

#endif 
