#include "RandomFish.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

// Function to print RandomFish details
void printRandomFish(RandomFish* randomFish) {
    printf("Age: {%d}, Pattern: {%s}, Color: {%s}, ",
        randomFish->age,
        randomFishPattern[randomFish->pattern],
        randomFishColor[randomFish->color]);
    printFishTimestamp(randomFish);
}

// Function to create a new RandomFish
RandomFish* createRandomFish() {
    RandomFish* result = (RandomFish*)calloc(1, sizeof(RandomFish));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    result->age = rand() % 10 + 1;
    result->pattern = rand() % eNofrandomFishPattern;
    result->color = rand() % eNofrandomFishColor;

    // Allocate memory for timestamp and set the current time
    FishTimestamp* timestamp = (FishTimestamp*)malloc(sizeof(FishTimestamp));
    if (timestamp != NULL) {
        timestamp->timestamp = time(NULL);
        result->extraInfo = timestamp;
    }
    else {
        result->extraInfo = NULL;
    }

    result->next = NULL; // Initialize next to NULL for new nodes

    return result;
}

 //Function to write RandomFish to a text file
//void writeRandomFish(RandomFish* random, FILE* file) {
//    fprintf(file, "%d,%d,%d,%lld\n", random->age, random->pattern, random->color,random->extraInfo);
//}

void writeRandomFish(RandomFish* random, FILE* file) {
    
    FishTimestamp* timestamp = (FishTimestamp*)random->extraInfo;

    if (timestamp != NULL) {
        fprintf(file, "%d,%d,%d,%lld\n", random->age, random->pattern, random->color, (long long int)timestamp->timestamp);
    }
    else {
        fprintf(file, "%d,%d,%d,%s\n", random->age, random->pattern, random->color, "No timestamp");
    }
}

// Function to read RandomFish from a text file
//RandomFish* readRandomFishFromFile(FILE* fp) {
//    RandomFish* random = (RandomFish*)calloc(1, sizeof(RandomFish));
//    if (random == NULL) {
//        printf("Memory allocation failed\n");
//        return NULL;
//    }
//
//    if (fscanf(fp, "%d,%d,%d\n", &random->age, (int*)&random->pattern, (int*)&random->color) != 3) {
//        free(random);
//        return NULL;
//    }
//    return random;
//}
RandomFish* readRandomFishFromFile(FILE* fp) {
    RandomFish* random = (RandomFish*)calloc(1, sizeof(RandomFish));
    if (random == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    long long timestamp_value;
    if (fscanf(fp, "%d,%d,%d,%lld\n", &random->age, (int*)&random->pattern, (int*)&random->color, &timestamp_value) != 4) {
        free(random);
        return NULL;
    }

    // Allocate and assign the timestamp if it's not zero
    if (timestamp_value != 0) {
        FishTimestamp* timestamp = (FishTimestamp*)malloc(sizeof(FishTimestamp));
        if (timestamp != NULL) {
            timestamp->timestamp = (time_t)timestamp_value;
            random->extraInfo = timestamp;
        }
        else {
            random->extraInfo = NULL;
        }
    }
    else {
        random->extraInfo = NULL;
    }

    return random;
}


// Function to write RandomFish to a binary file
void writeRandomFishToBinaryFile(RandomFish* random, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    fwrite(&random->age, sizeof(int), 1, file);
    fwrite(&random->pattern, sizeof(int), 1, file);
    fwrite(&random->color, sizeof(int), 1, file);
}

// Function to read RandomFish from a binary file
RandomFish* readRandomFishFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    RandomFish* random = (RandomFish*)calloc(1, sizeof(RandomFish));
    if (random == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    if (fread(&random->age, sizeof(int), 1, file) != 1 ||
        fread(&random->pattern, sizeof(int), 1, file) != 1 ||
        fread(&random->color, sizeof(int), 1, file) != 1) {
        free(random);
        return NULL;
    }

    return random;
}

// Function to free RandomFish and its extraInfo
void freeRandomFish(RandomFish* fish) {
    if (fish != NULL) {
        if (fish->extraInfo != NULL) {
            free(fish->extraInfo);
        }
        free(fish);
    }
}

// Function to print the timestamp of when the fish was added
void printFishTimestamp(RandomFish* fish) {
    if (fish != NULL && fish->extraInfo != NULL) {
        FishTimestamp* timestamp = (FishTimestamp*)fish->extraInfo;
        printf("Fish added at: %s", ctime(&timestamp->timestamp));
    }
    else {
        printf("No timestamp available.\n");
    }
}

// Function to add a new fish to the linked list
void addFishToList(RandomFish** head, RandomFish* newFish) {
    newFish->next = *head; 
    *head = newFish;       
}

// Function to print all fish in the linked list
void printFishList(RandomFish* head) {
    RandomFish* current = head;
    while (current != NULL) {
        printRandomFish(current);
        printf("\n"); 
        current = current->next;
    }
}

// Function to free all fish in the linked list
void freeFishList(RandomFish* head) {
    RandomFish* current = head;
    RandomFish* next;
    while (current != NULL) {
        next = current->next; 
        freeRandomFish(current); 
        current = next; 
    }
}
