#ifndef RANDOMFISH_H
#define RANDOMFISH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 20


typedef enum {
    ePoints, eStripes, eSlots, eNofrandomFishPattern
} eRandomFishPattern;

static const char* randomFishPattern[eNofrandomFishPattern] = { "Points", "Stripes", "Slots" };


typedef enum {
    eBlack, eRed, ePurple, eGreen, eBlue, eYellow, eNofrandomFishColor
} eRandomFishColor;

static const char* randomFishColor[eNofrandomFishColor] = { "Black", "Red", "Purple", "Green", "Blue", "Yellow" };

// Structure to hold timestamp information
typedef struct {
    time_t timestamp; // Timestamp of when the fish was added
} FishTimestamp;


typedef struct RandomFish {
    int age;
    eRandomFishPattern pattern;
    eRandomFishColor color;
    void* extraInfo; 
    struct RandomFish* next; 
} RandomFish;


void printRandomFish(RandomFish* randomFish);
RandomFish* createRandomFish();
void writeRandomFish(RandomFish* random, FILE* file);
RandomFish* readRandomFishFromFile(FILE* fp);
void writeRandomFishToBinaryFile(RandomFish* random, FILE* file);
RandomFish* readRandomFishFromBinaryFile(FILE* file);
void freeRandomFish(RandomFish* fish);
void printFishTimestamp(RandomFish* fish);
void addFishToList(RandomFish** head, RandomFish* newFish);
void printFishList(RandomFish* head);
void freeFishList(RandomFish* head);

#endif // RANDOMFISH_H
