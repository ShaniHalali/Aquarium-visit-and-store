#ifndef __SEA_CREATURE__
#define __SEA_CREATURE__
#pragma warning (disable:4996)
#include <stdio.h>


typedef enum {
	eDarkGreen, ePink, eAzuleBlue, eOrange, eDarkBlue, eDarkYellow, eNofSeaCreatureColors
} eSeaCreatureColor;


static const char* SeaCreatureColour[eNofSeaCreatureColors]
= { "Dark Green", "Pink", "Azule Blue","Orange", "Dark Blue", "Dark Yellow" };

typedef struct
{
	int age;
	int lifeSpan;
	eSeaCreatureColor color1;
	eSeaCreatureColor color2;

}SeaCreature;



eSeaCreatureColor getValidColour(const char* prompt);
void getValidColours(SeaCreature* creature);
SeaCreature* getSeaCreatureFromUser();
SeaCreature* createSeaCreature(int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2);
void writeSeaCreatureToFile(SeaCreature* seaCreature, FILE* file);
SeaCreature* readSeaCreatureFromFile(FILE* file);
void writeSeaCreatureToBinFile(SeaCreature* seaCreature, FILE* file);
SeaCreature* readSeaCreatureFromBinFile(FILE* file);

#endif 
