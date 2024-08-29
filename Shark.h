#ifndef SHARK_H
#define SHARK_H

#include "SeaCreatures.h"
#include "generalFunctions.h"


typedef struct {
    SeaCreature seaCreature;
    char name[50];
    double weight;
} Shark;


void getSharkFromUser(Shark* shark);
void printShark(const void* ptr);

int compareSharksName(const void* a, const void* b);
int compareSharksAge(const void* a, const void* b);
int compareSharksWeight(const void* a, const void* b);

Shark* createShark(const char* name, double weight, int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2);
void writeSharkToFile(Shark* shark, FILE* file);
Shark* readSharkFromFile(FILE* file);
void writeSharkToBinaryFile(Shark* shark, FILE* file);
Shark* readSharkFromBinaryFile(FILE* file);

#endif

