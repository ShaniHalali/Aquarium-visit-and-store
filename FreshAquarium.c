#include "FreshAquarium.h"
#include "generalFunctions.h"

FreshAquarium* initFreshAquarium() {
    FreshAquarium* result = (FreshAquarium*)calloc(1, sizeof(FreshAquarium));
    result->randomFish = (RandomFish**)calloc(MAX_ITEMS, sizeof(RandomFish*));
    for (int i = 0; i < MAX_ITEMS; i++) {
        result->randomFish[i] = NULL;
    }

    result->freshFish = (FreshFish**)calloc(MAX_ITEMS, sizeof(FreshFish*));
    for (int i = 0; i < MAX_ITEMS; i++) {
        result->freshFish[i] = NULL;
    }

    return result;
}

void writeFreshAquariumToTxtFile(FreshAquarium* freshAquarium, FILE* fp) {
    writeDolphinListToTxtFile(freshAquarium->dolphinLinkedList, fp);
    writeFreshFishesToTxtFile(freshAquarium->freshFish, freshAquarium->freshFishSize, fp);
    writeRandomFishesToFile(freshAquarium->randomFish, freshAquarium->sizeOfRandomFish, fp);
}

FreshAquarium* readFreshAquariumFromBinaryFile(FILE* fp) {
    FreshAquarium* result = initFreshAquarium();
    readDolphinListFromBinaryFile(result, fp);
    readFreshFishesFromBinaryFile(result, fp);
    readRandomFishesFromBinaryFile(result, fp);
    return result;
}

void writeFreshAquariumToBinaryFile(FreshAquarium* freshAquarium, FILE* fp) {
    writeDolphinListToBinaryFile(freshAquarium->dolphinLinkedList, fp);
    writeFreshFishesToBinaryFile(freshAquarium->freshFish, freshAquarium->freshFishSize, fp);
    writeRandomFishesToBinaryFile(freshAquarium->randomFish, freshAquarium->sizeOfRandomFish, fp);
}

void writeRandomFishesToBinaryFile(RandomFish** randomFish, int size, FILE* file) {
    fwrite(&size, sizeof(int), 1, file);
    for (int i = 0; i < size; i++) {
        writeRandomFishToBinaryFile(randomFish[i], file);
    }
}

void writeRandomFishesToFile(RandomFish** randomFish, int size, FILE* fp) {
    fprintf(fp, "%d\n", size);
    for (int i = 0; i < size; i++) {
        writeRandomFish(randomFish[i], fp);
    }
}

FreshAquarium* readFreshAquariumFromFile(FILE* fp) {
    FreshAquarium* result = initFreshAquarium();
    readDolphinListFromFile(result, fp);
    readFreshFishesFromFile(result, fp);
    readRandomFishesFromFile(result, fp);
    return result;
}

void readRandomFishesFromBinaryFile(FreshAquarium* fresh, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }
    int numOfRandomFishes = 0;
    fread(&numOfRandomFishes, sizeof(int), 1, file);
    for (int i = 0; i < numOfRandomFishes; i++) {
        RandomFish* randomFish = readRandomFishFromBinaryFile(file);
        addRandomFish(fresh, randomFish);
    }
}

void readRandomFishesFromFile(FreshAquarium* fresh, FILE* fp) {
    int numOfRandomFishes;
    if (fscanf(fp, "%d\n", &numOfRandomFishes) != 1) {
        printf("Failed to read the number of random fishes from the file!\n");
        return;
    }
    for (int i = 0; i < numOfRandomFishes; i++) {
        RandomFish* randomFish = readRandomFishFromFile(fp);
        addRandomFish(fresh, randomFish);
    }
}

void readDolphinListFromBinaryFile(FreshAquarium* fresh, FILE* fp) {
    if (fp == NULL) {
        printf("Invalid file!\n");
        return;
    }
    int numDolphins = 0;
    fread(&numDolphins, sizeof(int), 1, fp);
    for (int i = 0; i < numDolphins; i++) {
        Dolphin* dp = readDolphinFromBinFile(fp);
        insertDolphinLinkedList(fresh, dp);
    }
}

void readDolphinListFromFile(FreshAquarium* fresh, FILE* fp) {
    if (fp == NULL) {
        printf("Invalid file!\n");
        return;
    }
    int numDolphins;
    if (fscanf(fp, "%d\n", &numDolphins) != 1) {
        printf("Failed to read the number of dolphins from the file!\n");
        return;
    }
    for (int i = 0; i < numDolphins; i++) {
        Dolphin* dp = readDolphinFromFile(fp);
        insertDolphinLinkedList(fresh, dp);
    }
}

void writeDolphinListToBinaryFile(Dolphin* head, FILE* file) {
    if (head == NULL) {
        int count = 0;
        fwrite(&count, sizeof(int), 1, file);
        return;
    }
    int count = 0;
    Dolphin* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    fwrite(&count, sizeof(int), 1, file);
    current = head;
    while (current != NULL) {
        writeDolphinToBinaryFile(current, file);
        current = current->next;
    }
}
//
//void writeDolphinListToTxtFile(Dolphin* head, FILE* file) {
//    if (head == NULL) {
//        int count = 0;
//        fwrite(&count, sizeof(int), 1, file);
//        return;
//    }
//    int count = 0;
//    Dolphin* current = head;
//    while (current != NULL) {
//        count++;
//        current = current->next;
//    }
//    fprintf(file, "%d\n", count); // num of dolphins
//    current = head;
//    while (current != NULL) {
//        writeDolphinToFile(current, file);
//        current = current->next;
//    }
//}

void writeDolphinListToTxtFile(Dolphin* head, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    if (head == NULL) {
        // If the list is empty, write 0 to the file
        fprintf(file, "0\n");
        return;
    }

    int count = 0;
    Dolphin* current = head;
    // Count the number of dolphins in the list
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Write the number of dolphins to the file
    fprintf(file, "%d\n", count);

    // Write each dolphin to the file
    current = head;
    while (current != NULL) {
        writeDolphinToFile(current, file);
        current = current->next;
    }
}

void writeFreshFishesToBinaryFile(FreshFish** freshFishes, int size, FILE* fp) {
    fwrite(&size, sizeof(int), 1, fp);
    for (int i = 0; i < size; i++) {
        writeFreshFishToBinaryFile(freshFishes[i], fp);
    }
}

void writeFreshFishesToTxtFile(FreshFish** freshFishes, int size, FILE* fp) {
    fprintf(fp, "%d\n", size);
    for (int i = 0; i < size; i++) {
        writeFreshFishToTxtFile(freshFishes[i], fp);
    }
}

void readFreshFishesFromBinaryFile(FreshAquarium* freshAquarium, FILE* fp) {
    int numOfFreshFishes = 0;
    fread(&numOfFreshFishes, sizeof(int), 1, fp);
    for (int i = 0; i < numOfFreshFishes; i++) {
        FreshFish* freshFish = readFreshFishFromBinaryFile(fp);
        addFreshFish(freshAquarium, freshFish);
    }
}

void readFreshFishesFromFile(FreshAquarium* freshAquarium, FILE* fp) {
    int numOfFreshFishes;
    fread(&numOfFreshFishes, sizeof(int), 1, fp);
    for (int i = 0; i < numOfFreshFishes; i++) {
        FreshFish* freshFish = readFreshFishFromFile(fp);
        addFreshFish(freshAquarium, freshFish);
    }
}

void printAllFreshAquariums(const FreshAquarium* aquarium) {
    printf("\n=== Fresh Creatures ===\n\n");
    printf("--Dolphin List--\n");
    printDolphinList(aquarium->dolphinLinkedList);
    printf("--Random Fishes--\n");
    //Using general function(void*).
    printArr(aquarium->randomFish, aquarium->sizeOfRandomFish, printRandomFish);
    printf("--Fresh Fishes--\n");
    printAllFreshFishes(aquarium);
}

void printAllFreshFishes(const FreshAquarium* aquarium) {
    if (aquarium->freshFishSize == 0)
    {
        printf("No Fresh fish to display.\n");
    }
    for (int i = 0; i < aquarium->freshFishSize; i++) {
        printFreshFish(aquarium->freshFish[i]);
    }
}

void printDolphinList(Dolphin* head) {
    if (head == NULL) {
        printf("No dolphins to display.\n");
    }
    else {
        Dolphin* temp = head;
        while (temp != NULL) {
            printDolphin(temp);
            temp = temp->next;
        }
    }
}

void addFreshFish(FreshAquarium* freshAquarium, FreshFish* freshFish) {
    if (freshAquarium->freshFishSize == MAX_ITEMS) {
        printf("No Place for new fish\n");
        return;
    }
    freshAquarium->freshFish[freshAquarium->freshFishSize++] = freshFish;
}

void addRandomFish(FreshAquarium* freshAquarium, RandomFish* randomFish) {
    if (freshAquarium->sizeOfRandomFish == MAX_ITEMS) {
        printf("No Place for new fish\n");
        return;
    }
    freshAquarium->randomFish[freshAquarium->sizeOfRandomFish++] = randomFish;
}

void insertDolphinLinkedList(FreshAquarium* aquarium, Dolphin* dolphin) {
    Dolphin* head = aquarium->dolphinLinkedList;
    if (head == NULL) {
        aquarium->dolphinLinkedList = dolphin;
    }
    else {
        Dolphin* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = dolphin;
    }
}

void findOldestFish(const FreshFish** freshFishArray, int size) {
    if (size == 0) {
        printf("No fresh fish in the aquarium!\n");
        return;
    }

    int indexOfOldest = 0;
    for (int i = 1; i < size; ++i) {
        if (freshFishArray[i]->age > freshFishArray[indexOfOldest]->age) {
            indexOfOldest = i;
        }
    }
    printf("Oldest Fish Details:\n");
    printFreshFish(freshFishArray[indexOfOldest]);
}

void freeFreshAquarium(FreshAquarium* freshAquarium) {
    // Free randomFish array
    if (freshAquarium->randomFish != NULL) {
        for (int i = 0; i < freshAquarium->sizeOfRandomFish; i++) {
            free(freshAquarium->randomFish[i]);
        }
        free(freshAquarium->randomFish);
    }

    // Free freshFish array
    if (freshAquarium->freshFish != NULL) {
        for (int i = 0; i < freshAquarium->freshFishSize; i++) {
            freeFreshFish(freshAquarium->freshFish[i]);
        }
        free(freshAquarium->freshFish);
    }

    // Free dolphin linked list
    Dolphin* current = freshAquarium->dolphinLinkedList;
    while (current != NULL) {
        Dolphin* next = current->next;
        free(current);
        current = next;
    }

    // Free the FreshAquarium itself
    free(freshAquarium);
}
