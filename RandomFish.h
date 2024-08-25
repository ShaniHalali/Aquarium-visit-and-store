#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define MAX_ITEMS 20
#define OLDESTFISH(Fish){\
				printf("the oldest fish : "); \
				printf("name : %s ,", Fish->name); \
				printf("age : %d \n", Fish->age); \
}

typedef enum {
	ePoints, eStripes, eSlots, eNofrandomFishPattern
} eRandomFishPattern;


static const char* randomFishPattern[eNofrandomFishPattern]
= { "Points", "Stripes", "Slots" };


typedef enum {
	eBlack, eRed, ePurple, eGreen, eBlue, eYellow, eNofrandomFishColor
} eRandomFishColor;


static const char* randomFishColor[eNofrandomFishColor] = { "Black", "Red", "Purple","Green", "Blue", "Yellow" };


typedef struct RandomFish
{
	int age;
	enum eRandomFishPattern pattern;
	enum eRandomFishColor color;
} RandomFish;


void printRandomFish(RandomFish* randomFish);
RandomFish* createRandomFish();
void writeRandomFish(RandomFish* random, FILE* file);
RandomFish* readRandomFishFromFile(FILE* fp);
void writeRandomFishToBinaryFile(RandomFish* random, FILE* file);
RandomFish* readRandomFishFromBinaryFile(FILE* file);
