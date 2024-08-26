#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#include "Dolphin.h"
#include <stdio.h>
#include <stdlib.h>

int countDolphinsInList(const Dolphin* head) {
	int count = 0;  


	while (head != NULL) {
		count++;          
		head = head->next; 
	}

	return count; 
}



Dolphin* searchDolphinByName(const char tav, const Dolphin* head)
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
	printf("Enter the dolphin name by capital letter:");
	do {
		tav = getchar();
		if (searchDolphinByName(tav, head) != NULL) {
			printf("this name = %c is already taken \n", tav);
			printf("Enter the dolphin name by capital letter:");
		}
	} while (tav < 'A' || tav>'Z' || searchDolphinByName(tav, head) != NULL);

	double minLength = 10;
	double length = 0;
	printf("Enter the dolphin length (at least %.1lf) :", minLength);

	do {
		
		scanf("%lf", &length);
		if (length < minLength) {
			printf("%.2lf is smaller than the minimum length \n", length);
			printf("Please Enter the dolphin length (at least %.1lf) :", minLength);
		}
	} while (length < minLength);


	while (fgetchar() != '\n');

	//each friendshipValue of the Dolphins that already exist will rise by 1
	friendshipValueRiseByOne(head);

	Dolphin* newDolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
	if (newDolphin == NULL) {
		printf("Error creating new dolphin \n");
		return;
	}
	newDolphin->length = length;
	//friendshipValue equal to the num of the exist dolphins before adding a new one
	newDolphin->friendshipValue = countDolphinsInList(head)-1;
	newDolphin->nameByChar = tav;
	
	printf("\nnew Dolphin added successfully! is details are : \n");
	PRINTALLDOLPHIND(newDolphin);
	return newDolphin;
}

void printDolphin(const Dolphin* dolphin) {
	PRINTALLDOLPHIND(dolphin);
}

int removeByFriendshipValue(Dolphin** head, int friendShipValue) {
	int removedCount = 0;

	// Handle the case where the head needs to be removed
	while (*head != NULL && (*head)->friendshipValue <= friendShipValue) {
		Dolphin* temp = *head;
		*head = (*head)->next;
		free(temp);
		removedCount++;
	}

	// Now handle the rest of the list
	Dolphin* current = *head;
	while (current != NULL && current->next != NULL) {
		if (current->next->friendshipValue <= friendShipValue) {
			Dolphin* temp = current->next;
			current->next = temp->next;
			free(temp);
			removedCount++;
		}
		else {
			current = current->next;
		}
	}

	//friendshipValue of each Dolphin will decrease by the number of removed Dolphins  
	if (removedCount > 0) 
	{
		friendshipValueDecreaseByRemovedDolphins(head, removedCount);
		
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


void friendshipValueRiseByOne(Dolphin* head)
{
	while (head != NULL) {
		head->friendshipValue = head->friendshipValue + 1;
		head = head->next;
	}

}

void friendshipValueDecreaseByRemovedDolphins(Dolphin** head, const int removedDolphinsCount) {
	Dolphin* current = *head;
	while (current != NULL) {
		current->friendshipValue -= removedDolphinsCount;
		current = current->next;
	}
}



// Function to safely read an integer from user input
int readFriendshipIntegerFromUser() {
	int value;
	char term; // Variable to check for any extra characters in the input

	
	printf("Enter the friendship value to remove dolphins (at least 0): ");

	while (1) {
		// Read the integer value and any extra characters
		if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
			// If the input is not valid, clear the input buffer
			printf("Invalid input. Please enter a valid integer value: ");
			while (getchar() != '\n'); // Clear invalid input from buffer
		}
		else if (value < 0) {
			printf("Please enter a non-negative integer: ");
		}
		else {
			return value;
		}
	}
}

void removeAndPrintChangesInDolphinsList(Dolphin* head) {
	printf("================BEFORE==============\n");
	printDolphinList(head);

	printf("================AFTER==============\n");

	// Read and validate user input for friendship value
	int friendshipValue = readFriendshipIntegerFromUser();

	// Remove dolphins with friendshipValue less than the user input
	int removed = removeByFriendshipValue(&(head), friendshipValue);
	printf("%d dolphins removed,\neach Dolphin's FriendshipValue will decrease by the number of removed Dolphins = %d\n \n", removed, removed);

	// Print the dolphin list after changes
	printDolphinList(head);
}
