#include"RandomFish.h"


void printRandomFish(RandomFish* randomFish)
{
    printf("Age: {%d} , Pattern: {%s} , Color: {%s} \n",
        randomFish->age,
        randomFishPattern[randomFish->pattern],
        randomFishColor[randomFish->color]);
}

RandomFish* createRandomFish() {
    RandomFish* result = (RandomFish*)calloc(1, sizeof(RandomFish));
    result->age = rand() % (10) + 1;
    result->pattern = rand() % (3);
    result->color = rand() % (5);
    return result;
}


void writeRandomFish(RandomFish* random, FILE* file) {

    fprintf(file, "%d,%d,%d\n", random->age, random->pattern, random->color);

}

RandomFish* readRandomFishFromFile(FILE* fp) {
    RandomFish* random = (RandomFish*)calloc(1, sizeof(RandomFish));
    if (random == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    if (fscanf(fp, "%d,%d,%d\n", &random->age, (int*)&random->pattern, (int*)&random->color) != 3) {
        return NULL;
    }
    return random;

}
void writeRandomFishToBinaryFile(RandomFish* random, FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return;
    }

    // Write the RandomFish structure to the file
    fwrite(&random->age, sizeof(int), 1, file);
    fwrite(&random->pattern, sizeof(int), 1, file);
    fwrite(&random->color, sizeof(int), 1, file);
}

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

    // Read the RandomFish structure from the file
    if (fread(&random->age, sizeof(int), 1, file) != 1 ||
        fread(&random->pattern, sizeof(int), 1, file) != 1 ||
        fread(&random->color, sizeof(int), 1, file) != 1) {
        free(random);
        return NULL;
    }

    return random;
}
