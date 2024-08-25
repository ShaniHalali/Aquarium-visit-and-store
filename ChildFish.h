#pragma once
#include "FreshFish.h"

#define PRINTCHILD(ChildFish){\
				printf("Fish number : %d , ",ChildFish->fishNumber);\
				printf("Parents names : %s \n",ChildFish->parentsNames);\
				printf(" \n");\
}

typedef struct
{
	char* parentsNames;
	FreshFish* firstParent;
	FreshFish* secondParent;
	int fishNumber;
}ChildFish;

void addNewBornChildFish(int freshFishAmount, FreshFish** arrOfFreshFish, ChildFish** arrOfChildFish, int* indexAmountChilsFish);
void printChildFish(ChildFish* child);
void writeFreshFishToTxtFile(FreshFish*, FILE* fp);
void writeChildFishToTxtFile(ChildFish*, FILE* fp);
FreshFish* readFreshFishFromFile(FILE* fp);
FreshFish* createFreshFish(int age, int lifeSpan, char* name);
ChildFish* createChildFIsh(int fishNumber, FreshFish* firstParent, FreshFish* secondParent);
void writeFreshFishToBinaryFile(FreshFish* fish, FILE* file);
void writeChildFishToBinaryFile(ChildFish* child, FILE* fp);
ChildFish* readChildFishFromBinaryFile(FILE* file);
FreshFish* readFreshFishFromBinaryFile(FILE* file);
FreshFish* createFreshFishFromUser();