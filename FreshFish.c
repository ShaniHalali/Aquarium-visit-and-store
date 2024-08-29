#include "FreshFish.h"



void printFreshFish(FreshFish* f) {
    PRINT(f);
}

void printarray(void* array, size_t size, size_t elementsize, void(printFunc)(void))
{
    char* ptr = (char*)array;
    for (size_t i = 0; i < size; i++)
        printFunc(ptr + i * elementsize);
}

void freeFreshFish(FreshFish* fish) {
    if (fish != NULL) {
        // Free dynamically allocated memory for name
        if (fish->name != NULL) {
            free(fish->name);
        }

        // Free the FreshFish itself
        free(fish);
    }
}

FreshFish* createFreshFish(int age, int lifeSpan, const char* name) {
    FreshFish* fish = (FreshFish*)malloc(sizeof(FreshFish));
    if (fish == NULL) {
        return NULL;
    }
    fish->age = age;
    fish->lifeSpan = lifeSpan;
    fish->name = strdup(name);
    return fish;
}

FreshFish* createFreshFishFromUser() {
    int age, lifeSpan;
    char name[100];

    // Age input validation
    do {
        printf("Enter age (positive integer): ");
        if (scanf("%d", &age) != 1 || age <= 0) {
            printf("Invalid input. Age must be a positive integer greater than zero.\n");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    } while (1);

    // Life span input validation
    do {
        printf("Enter life span (must be greater than or equal to age): ");
        if (scanf("%d", &lifeSpan) != 1 || lifeSpan < age) {
            printf("Invalid input. Life span must be greater than or equal to age.\n");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    } while (1);

    // Name input validation
    do {
        printf("Enter name:");
        scanf("%s", name);

        if (strlen(name) == 0) {
            printf("Invalid input. Name cannot be empty.\n");
        }
        else {
            break;
        }
    } while (1);

    return createFreshFish(age, lifeSpan, name);
}

void writeFreshFishToBinaryFile(FreshFish* fish, FILE* file) {
    fwrite(&fish->age, sizeof(int), 1, file);
    fwrite(&fish->lifeSpan, sizeof(int), 1, file);
    int nameLength = strlen(fish->name) + 1;
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(fish->name, sizeof(char), nameLength, file);
}

void writeFreshFishToTxtFile(FreshFish* fish, FILE* file) {
   // fprintf(file, "%d,%d,%s\n", fish->age, fish->lifeSpan, fish->name);
    fprintf(file, "%s,%d,%d\n", fish->name, fish->age, fish->lifeSpan);
}

FreshFish* readFreshFishFromBinaryFile(FILE* file) {
    FreshFish* fish = (FreshFish*)malloc(sizeof(FreshFish));
    if (fish == NULL) {
        return NULL;
    }
    fread(&fish->age, sizeof(int), 1, file);
    fread(&fish->lifeSpan, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    fish->name = (char*)malloc(nameLength);
    fread(fish->name, sizeof(char), nameLength, file);
    return fish;
}

FreshFish* readFreshFishFromFile(FILE* file) {
    FreshFish* fish = (FreshFish*)malloc(sizeof(FreshFish));
    if (fish == NULL) {
        return NULL;
    }
    char name[100];
    fscanf(file, "%d,%d,%s\n", &fish->age, &fish->lifeSpan, name);
    fish->name = strdup(name);
    return fish;
}
