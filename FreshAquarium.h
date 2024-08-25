#pragma once
#include"FreshFish.h"
#include"Dolphin.h"
#include "RandomFish.h"
#include "ChildFish.h"


typedef struct FreshAquarium {
	RandomFish** randomFish;
	int sizeOfRandomFish;
	FreshFish** freshFish;
	int freshFishSize;
	Dolphin* dolphinLinkedList;
}FreshAquarium;

FreshAquarium* initFreshAquarium();
void addFreshFish(FreshAquarium* freshAquarium, FreshFish* freshFish1, FreshFish* freshFish2);
void addRandomFish(FreshAquarium* freshAquarium, RandomFish* freshFish);
void insertDolphinLinkedList(FreshAquarium* aquarium, Dolphin* dolphin);
void printAllFreshAquariums(const FreshAquarium* aquarium);
void printAllFreshFishes(const FreshAquarium* aquarium);
FreshAquarium* readFreshAquariumFromBinaryFile(FILE* fp);
void oldestFish(FreshFish** arrOfFreshFish, int amount);
void writeFreshAquariumToTxtFile(FreshAquarium* freshAquarium, FILE* fp);
void writeFreshAquariumToBinaryFile(FreshAquarium* freshAquarium, FILE* fp);
void readDolphinListFromFile(FreshAquarium* fresh, FILE* fp);
void readDolphinListFromBinaryFile(FreshAquarium* fresh, FILE* fp);
void readRandomFishesFromBinaryFile(FreshAquarium* fresh, FILE* file);
FreshAquarium* readFreshAquariumFromFile(FILE* fp);
void writeDolphinListToTxtFile(Dolphin* head, FILE* file);
void writeDolphinListToBinaryFile(Dolphin* head, FILE* file);
void writeFreshFishesToBinaryFile(FreshFish** frehFishes, int size, FILE* fp);
void writeFreshFishesToTxtFile(FreshFish** frehFishes, int size, FILE* fp);
void readFreshFishesFromBinaryFile(FreshAquarium* freshAquarium, FILE* fp);
void readFreshFishesFromFile(FreshAquarium* fresh, FILE* fp);
void writeRandomFishesToFile(RandomFish** randomFish, int size, FILE* fp);
void readRandomFishesFromFile(FreshAquarium* fresh, FILE* fp);
void writeRandomFishesToBinaryFile(RandomFish** randomFish, int size, FILE* file);
void findOldestFish(const FreshFish** freshFishArray, int size);
void getRandomFishFromUser(RandomFish* pFish);
void freeFreshAquarium(FreshAquarium* freshAquarium);
