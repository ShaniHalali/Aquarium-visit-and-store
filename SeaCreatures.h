#ifndef __SEA_CREATURE__
#define __SEA_CREATURE__
#pragma warning (disable:4996)
#include <stdio.h>


typedef enum {
	eDarkGreen, ePink, eAzuleBlue, eOrange, eDarkBlue, eDarkYellow, eNofSeaCreatureColours
} eSeaCreatureColour;


static const char* SeaCreatureColour[eNofSeaCreatureColours]
= { "Dark Green", "Pink", "Azule Blue","Orange", "Dark Blue", "Dark Yellow" };

typedef struct
{
	int age;
	int lifeSpan;
	eSeaCreatureColour colour1;
	eSeaCreatureColour colour2;

}SeaCreature;



eSeaCreatureColour	getColourFromUser();
void getColoursForSeaCreature(SeaCreature* pPer);
void getSeaCreatureFromUser(SeaCreature* pPer);
void printSeaCreature(const SeaCreature* pPer);
SeaCreature* createSeaCreature(int age, int lifeSpan, eSeaCreatureColour color1, eSeaCreatureColour color2);
void writeSeaCreatureToFile(SeaCreature* seaCreature, FILE* file);
SeaCreature* readSeaCreatureFromFile(FILE* file);
void writeSeaCreatureToBinFile(SeaCreature* seaCreature, FILE* file);
SeaCreature* readSeaCreatureFromBinFile(FILE* file);

#endif 