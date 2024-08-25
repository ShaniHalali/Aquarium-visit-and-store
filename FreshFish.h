#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define MAX_ITEMS 20

#define PRINT(Fish){\
				printf("name : %s ,",Fish->name);\
				printf("lifeSpan : %d , ", Fish->lifeSpan); \
				printf("age : %d \n",Fish->age);\
}

struct ChildFish;

typedef struct
{
	int age;
	int lifeSpan;
	char* name;
	struct ChildFish* child;
}FreshFish;


void printFreshFish(FreshFish* fish);
void printarray(void* array, size_t size, size_t elementsize, void(printFunc)(void));
void oldestFish(FreshFish** arrOfFreshFish, int amount);
void freeFreshFish(FreshFish* fish);