#pragma once
#include <stdio.h>
#include "generalFunctions.h"
#define PRINTALLDOLPHIND(Fish) {\
    printf("Name: {%c}, ", Fish->nameByChar);\
    printf("Length: {%.2lf}, ", Fish->length);\
    printf("Friendship Value: {%d}\n", Fish->friendshipValue);\
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
