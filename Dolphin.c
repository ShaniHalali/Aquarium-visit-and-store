#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#include "Dolphin.h"
#include <stdio.h>
#include <stdlib.h>


Dolphin* searchDolphinByName(char tav, Dolphin* head)
{
	Dolphin* temp = head;
	while (temp != NULL)
	{
		if (temp->nameByChar == tav) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

Dolphin* getDolphinFromUser(Dolphin* head) {
	char tav;
	while (fgetchar() != '\n');
	do {
		printf("Enter the dolphin name by capital letter:");
		tav = getchar();
		if (searchDolphinByName(tav, head) != NULL) {
			printf("this name = %c is already taken \n", tav);
		}
	} while (tav < 'A' || tav>'Z' || searchDolphinByName(tav, head) != NULL);
	printf("Enter the dolphin length:");
	double length = 0;
	scanf("%lf", &length);
	while (fgetchar() != '\n');
	Dolphin* newDolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
	if (newDolphin == NULL) {
		printf("Error creating new dolphin \n");
		return;
	}
	newDolphin->length = length;
	newDolphin->friendshipValue = 10;
	newDolphin->nameByChar = tav;
	return newDolphin;
}

void printDolphin(Dolphin* dolphin) {
	PRINTALLDOLPHIND(dolphin);
}
int removeByFriendshipValue(Dolphin** head, int friendShipValue) {
	int removedCount = 0;

	// Handle the case where the head needs to be removed
	while (*head != NULL && (*head)->friendshipValue < friendShipValue) {
		Dolphin* temp = *head;
		*head = (*head)->next;
		free(temp);
		removedCount++;
	}

	// Now handle the rest of the list
	Dolphin* current = *head;
	while (current != NULL && current->next != NULL) {
		if (current->next->friendshipValue < friendShipValue) {
			Dolphin* temp = current->next;
			current->next = temp->next;
			free(temp);
			removedCount++;
		}
		else {
			current = current->next;
		}
	}

	return removedCount;
}



Dolphin* createDolphin(int friendshipValue, double length, char nameByChar) {
	Dolphin* newDolphin = (Dolphin*)malloc(sizeof(Dolphin));
	if (newDolphin == NULL) {
		printf("Memory allocation failed!\n");
		exit(1);
	}
	newDolphin->friendshipValue = friendshipValue;
	newDolphin->length = length;
	newDolphin->nameByChar = nameByChar;
	newDolphin->next = NULL;
	return newDolphin;
}

void writeDolphinToBinaryFile(Dolphin* dolphin, FILE* file) {
	if (dolphin == NULL || file == NULL) {
		printf("Invalid input parameters!\n");
		return;
	}
	fwrite(&dolphin->friendshipValue, sizeof(int), 1, file);
	writeDoubleToBinaryFile(dolphin->length, file);
	//fwrite(&dolphin->length, sizeof(double), 1, file);
	fwrite(&dolphin->nameByChar, sizeof(char), 1, file);
}

void writeDolphinToFile(Dolphin* dolphin, FILE* file) {
	if (dolphin == NULL || file == NULL) {
		printf("Invalid input parameters!\n");
		return;
	}
	fprintf(file, "%d,%.2f,%c\n", dolphin->friendshipValue, dolphin->length, dolphin->nameByChar);
}

Dolphin* readDolphinFromFile(FILE* file) {
	if (file == NULL) {
		printf("Invalid file!\n");
		return NULL;
	}

	Dolphin* dolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
	if (dolphin == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	if (fscanf(file, "%d,%lf,%c ", &dolphin->friendshipValue, &dolphin->length, &dolphin->nameByChar) != 3) {
		printf("Failed to read Dolphin details from file!\n");
		free(dolphin);
		return NULL;
	}

	return dolphin;
}


Dolphin* readDolphinFromBinFile(FILE* file) {
	if (file == NULL) {
		printf("Invalid file!\n");
		return NULL;
	}

	Dolphin* dolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
	if (dolphin == NULL) {
		printf("Memory allocation failed!\n");
		return NULL;
	}

	fread(&dolphin->friendshipValue, sizeof(int), 1, file);
	dolphin->length = readDoubleFromBinaryFile(file);
	//writeDoubleToBinaryFile(dolphin->length, file);
	//fread(&dolphin->length, sizeof(double), 1, file);
	fread(&dolphin->nameByChar, sizeof(char), 1, file);

	return dolphin;
}

void removeAndPrintChangesInDolphinsList(Dolphin* head)
{
	
	printf("================BEFORE==============\n");
	printDolphinList(head);
	printf("================AFTER==============\n");
	int removed = removeByFriendshipValue(&(head), 1);
	printf(" %d dolphins removed \n", removed);
	printDolphinList(head);
}
