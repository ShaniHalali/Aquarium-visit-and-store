#pragma once
#include <stdio.h>
#include "generalFunctions.h"
#define PRINTALLDOLPHIND(Fish){\
				printf("name : %s ,",->name);\
				printf("length : %lf ,",Fish->age);\
				printf("friendshipValue: %d \n",Fish->age);\
				printf("\n");\
}


typedef struct Dolphin {
	int friendshipValue;
	double length;
	struct Dolphin* next;
	char nameByChar;
}Dolphin;

Dolphin* getDolphinFromUser(Dolphin* head);
Dolphin* searchDolphinByName(char tav, Dolphin* head);
void printDolphinList(Dolphin* head);
int removeByFriendshipValue(Dolphin* head, int friendShipValue);
Dolphin* createDolphin(int friendshipValue, double length, char nameByChar);
void printDolphin(Dolphin* dolphin);
void writeDolphinToBinaryFile(Dolphin* dolphin, FILE* file);
void writeDolphinToFile(Dolphin* dolphin, FILE* file);
Dolphin* readDolphinFromFile(FILE* file);
Dolphin* readDolphinFromBinFile(FILE* file);