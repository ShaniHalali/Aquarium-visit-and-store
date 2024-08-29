#include "SaltAquarium.h"
#include "generalFunctions.h"
#include <stdio.h>
#include <stdlib.h>

SaltAquarium* initSaltAquarium() {

    SaltAquarium* result = (SaltAquarium*)calloc(1, sizeof(SaltAquarium));
    if (!result) {
        printf("Memory allocation failed for SaltAquarium\n");
        return NULL;
    }
    return result;
}

void printAllSaltAquariums(const SaltAquarium* aquarium) {
    printf("\n=== SaltAquarium Creatures ===\n\n");

    printf("--Sea creatures--\n");
    if (aquarium->seaCreatures != NULL && aquarium->numSeaCreatures > 0) {
        //Using general function(void*).
        printArr((const void**)aquarium->seaCreatures, aquarium->numSeaCreatures, (void (*)(const void*))printSeaCreature);
    }
    else {
        printf("There are no Sea creatures...\n");
    }

    printf("\n--Sharks--\n");
    if (aquarium->sharks != NULL && aquarium->numSharks > 0) {
        //Using general function(void*).
        printArr((const void**)aquarium->sharks, aquarium->numSharks, (void (*)(const void*))printShark);
    }
    else {
        printf("No sharks to display.\n");
    }

    printf("\n--Clown fishes--\n");
    if (aquarium->clownFishes != NULL && aquarium->numClownFishes > 0) {
        printArr((const void**)aquarium->clownFishes, aquarium->numClownFishes, (void (*)(const void*))printClownFish);
    }
    else {
        printf("No Clown fish to display.\n");
    }
}

//-------------------------------SeaCreatures------------------------------------//


void addSeaCreature(SaltAquarium* saltAquarium, SeaCreature* newCreature) {
    if (!saltAquarium || !newCreature) {
        printf("Invalid aquarium or sea creature.\n");
        return;
    }
    saltAquarium->numSeaCreatures++;
    saltAquarium->seaCreatures = (SeaCreature**)realloc(saltAquarium->seaCreatures, saltAquarium->numSeaCreatures * sizeof(SeaCreature*));
    saltAquarium->seaCreatures[saltAquarium->numSeaCreatures - 1] = newCreature;
}


void ageAllSeaCreatures(SaltAquarium* aquarium) {
    int i = 0;
    while (i < aquarium->numSeaCreatures) {
        SeaCreature* currentSeaCreature = aquarium->seaCreatures[i];
        if (currentSeaCreature->age < currentSeaCreature->lifeSpan - 1) {
            currentSeaCreature->age++;
            printf("\nSea creature aged by one year.\n");
            i++;
        }
        else {
            printf("\nSea creature at index %d has reached its maximum lifespan and has been removed.\n", i);
            free(currentSeaCreature);
            for (int j = i; j < (aquarium->numSeaCreatures - 1); j++) {
                aquarium->seaCreatures[j] = aquarium->seaCreatures[j + 1];
            }
            aquarium->numSeaCreatures--;
        }
    }
}

//-------------------------------Sharks------------------------------------//

void addShark(SaltAquarium* saltAquarium, Shark* shark) {
    if (!saltAquarium || !shark) {
        printf("Invalid aquarium or shark.\n");
        return;
    }

    Shark** temp = (Shark**)realloc(saltAquarium->sharks, (saltAquarium->numSharks + 1) * sizeof(Shark*));
    if (!temp) {
        printf("Memory allocation failed for sharks\n");
        return; // If realloc fails, do not update the pointer
    }
    saltAquarium->sharks = temp;
    saltAquarium->sharks[saltAquarium->numSharks++] = shark;
}

void ageAllSharks(SaltAquarium* aquarium) {
    int i = 0;
    while (i < aquarium->numSharks) {
        Shark* currentShark = aquarium->sharks[i];
        if (currentShark->seaCreature.age < currentShark->seaCreature.lifeSpan - 1) {
            currentShark->seaCreature.age++;
            printf("\nShark %s aged by one year.\n", currentShark->name);
            i++;
        }
        else {
            printf("\nShark %s has reached its maximum lifespan and has been removed.\n", currentShark->name);

            free(currentShark);
            for (int j = i; j < (aquarium->numSharks - 1); j++) {
                aquarium->sharks[j] = aquarium->sharks[j + 1];
            }
            aquarium->numSharks--;
        }
    }
}

Shark* findSharkByAge(SaltAquarium* aquarium, int age) {
    qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksAge);
    Shark** pShark = NULL;
    Shark* temp = createShark("", 0, age, 0, 0, 0);
    pShark = (Shark**)bsearch(&temp, aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksAge);
    if (pShark != NULL) {
        return *pShark;
    }
    return NULL;
}
Shark* findSharkByWeight(SaltAquarium* aquarium, double weight) {
    qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksWeight);
    Shark** pShark = NULL;
    Shark* temp = createShark("", weight, 0, 0, 0, 0);
    pShark = (Shark**)bsearch(&temp, aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksWeight);
    if (pShark != NULL) {
        return *pShark;
    }
    return NULL;
}
Shark* findSharkByName(SaltAquarium* aquarium, char* name) {
    qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksName);

    Shark* temp = createShark(name, 0, 0, 0, 0, 0);

    Shark** pShark = (Shark**)bsearch(&temp, aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksName);

    if (pShark != NULL) {
        return *pShark;
    }
    return NULL;
}

void sortSharksMenu(SaltAquarium* aquarium) {
    int choice;
    do {
        printf("\nChoose how to sort the sharks:\n");
        printf("1. Sort by name\n");
        printf("2. Sort by age\n");
        printf("3. Sort by weight\n");
        printf("4. Exit sorting menu\n");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksName);
            printf("\nSharks sorted by name.\n");
            printArr(aquarium->sharks, aquarium->numSharks, printShark);
            return;
        case 2:
            qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksAge);
            printf("\nSharks sorted by age.\n");
            printArr(aquarium->sharks, aquarium->numSharks, printShark);
            return;
        case 3:
            qsort(aquarium->sharks, aquarium->numSharks, sizeof(Shark*), compareSharksWeight);
            printf("\nSharks sorted by weight.\n");
            printArr(aquarium->sharks, aquarium->numSharks, printShark);
            return;
        case 4:
            printf("\nExiting sorting menu.\n");
            return;
        default:
            printf("\nInvalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (1);
}
void sharkSearchMenu(SaltAquarium* aquarium) {
    int choice;
    do {
        printf("\nShark Search Menu:\n");
        printf("1. Search by name\n");
        printf("2. Search by age\n");
        printf("3. Search by weight\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char name[50];
            printf("Enter the name of the shark: ");
            scanf("%s", name);
            Shark* result = findSharkByName(aquarium, name);
            if (result != NULL) {
                printf("Found shark: %s\n", result->name);
            }
            else {
                printf("Shark not found.\n");
            }
            break;
        }
        case 2: {
            int age;
            printf("Enter the age of the shark: ");
            scanf("%d", &age);
            Shark* result = findSharkByAge(aquarium, age);
            if (result != NULL) {
                printf("Found shark: %s\n", result->name);
            }
            else {
                printf("Shark not found.\n");
            }
            break;
        }
        case 3: {
            double weight;
            printf("Enter the weight of the shark: ");
            scanf("%lf", &weight);
            Shark* result = findSharkByWeight(aquarium, weight);
            if (result != NULL) {
                printf("Found shark: %s\n", result->name);
            }
            else {
                printf("Shark not found.\n");
            }
            break;
        }
        case 4:
            printf("Exiting search menu.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
}

//-------------------------------ClownFish------------------------------------//

void addClownFish(SaltAquarium* saltAquarium, ClownFish* clownFish) {
    if (!saltAquarium || !clownFish) {
        printf("Invalid aquarium or clown fish.\n");
        return;
    }

    // Attempt to reallocate memory to accommodate the new clown fish
    ClownFish** temp = (ClownFish**)realloc(saltAquarium->clownFishes, (saltAquarium->numClownFishes + 1) * sizeof(ClownFish*));
    if (!temp) {
        printf("Memory allocation failed for clown fishes\n");
        return; // If realloc fails, do not update the pointer
    }

    saltAquarium->clownFishes = temp; // Update the pointer to the newly allocated memory
    saltAquarium->clownFishes[saltAquarium->numClownFishes++] = clownFish; // Add the new clown fish to the array
}


void ageAllClownFishes(SaltAquarium* aquarium) {
    int i = 0;
    while (i < aquarium->numClownFishes) {
        ClownFish* currentClownFish = aquarium->clownFishes[i];
        if (currentClownFish->seaCreature.age < currentClownFish->seaCreature.lifeSpan - 1) {
            currentClownFish->seaCreature.age++;
            printf("\nClownfish %s aged by one year.\n", currentClownFish->name);
            i++;
        }
        else {
            printf("\nClownfish %s has reached its maximum lifespan and has been removed.\n", currentClownFish->name);

            free(currentClownFish);
            for (int j = i; j < (aquarium->numClownFishes - 1); j++) {
                aquarium->clownFishes[j] = aquarium->clownFishes[j + 1];
            }
            aquarium->numClownFishes--;
        }
    }
}

//-------------------------------------------------------------------//

void writeSaltAquariumToTxtFile(SaltAquarium* saltAquarium, FILE* fp) {
    fprintf(fp, "%d\n", saltAquarium->numSeaCreatures);
    for (int i = 0; i < saltAquarium->numSeaCreatures; i++)
    {
        writeSeaCreatureToFile(saltAquarium->seaCreatures[i], fp);
    }
    fprintf(fp, "%d\n", saltAquarium->numSharks);
    for (int i = 0; i < saltAquarium->numSharks; i++)
    {
        writeSharkToFile(saltAquarium->sharks[i], fp);
    }

    fprintf(fp, "%d\n", saltAquarium->numClownFishes);
    for (int i = 0; i < saltAquarium->numClownFishes; i++)
    {
        writeClownFishToFile(saltAquarium->clownFishes[i], fp);
    }

}

void writeSaltAquariumToBinaryFile(SaltAquarium* saltAquarium, FILE* fp) {
    fwrite(&saltAquarium->numSeaCreatures, sizeof(int), 1, fp);
    for (int i = 0; i < saltAquarium->numSeaCreatures; i++)
    {
        writeSeaCreatureToBinFile(saltAquarium->seaCreatures[i], fp);

    }
    fwrite(&saltAquarium->numSharks, sizeof(int), 1, fp);
    for (int i = 0; i < saltAquarium->numSharks; i++)
    {
        writeSharkToBinaryFile(saltAquarium->sharks[i], fp);
    }

    fwrite(&saltAquarium->numClownFishes, sizeof(int), 1, fp);
    for (int i = 0; i < saltAquarium->numClownFishes; i++)
    {
        writeClownFishToBinaryFile(saltAquarium->clownFishes[i], fp);
    }

}

SaltAquarium* readSaltAquariumFromFile(FILE* fp) {
    SaltAquarium* salt = (SaltAquarium*)calloc(1, sizeof(SaltAquarium));
    int numSeaCreatures;
    if (fscanf(fp, "%d\n", &numSeaCreatures) != 1) {
        printf("Failed to read the number of dolphins from the file!\n");
        return NULL;
    }
    for (int i = 0; i < numSeaCreatures; i++)
    {
        SeaCreature* seaCreature = readSeaCreatureFromFile(fp);
        addSeaCreature(salt, seaCreature);
    }
    int numOfSharks;
    if (fscanf(fp, "%d\n", &numOfSharks) != 1) {

        return NULL;
    }
    for (int i = 0; i < numOfSharks; i++)
    {
        Shark* seaCreature = readSharkFromFile(fp);
        addShark(salt, seaCreature);
    }
    int numOfCorals;
    if (fscanf(fp, "%d\n", &numOfCorals) != 1) {
        return NULL;
    }


    int numOfClownFishes;
    if (fscanf(fp, "%d\n", &numOfClownFishes) != 1) {
        return NULL;
    }
    for (int i = 0; i < numOfClownFishes; i++)
    {
        ClownFish* clownFish = readClownFishFromFile(fp);
        addClownFish(salt, clownFish);

    }
    return salt;
}

SaltAquarium* readSaltAquariumFromBinaryFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    SaltAquarium* salt = (SaltAquarium*)calloc(1, sizeof(SaltAquarium));
    if (salt == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int numSeaCreatures;
    if (fread(&numSeaCreatures, sizeof(int), 1, file) != 1) {
        printf("Failed to read the number of sea creatures from the file!\n");
        free(salt);
        return NULL;
    }


    for (int i = 0; i < numSeaCreatures; i++) {
        SeaCreature* seaCreature = readSeaCreatureFromBinFile(file);
        addSeaCreature(salt, seaCreature);
    }

    int numOfSharks;
    if (fread(&numOfSharks, sizeof(int), 1, file) != 1) {
        printf("Failed to read the number of sharks from the file!\n");
        return NULL;
    }

    // Read sharks
    for (int i = 0; i < numOfSharks; i++) {
        Shark* shark = readSharkFromBinaryFile(file);
        addShark(salt, shark);
    }

    int numOfCorals;
    if (fread(&numOfCorals, sizeof(int), 1, file) != 1) {

        printf("Failed to read the number of corals from the file!\n");
        return NULL;
    }



    int numOfClownFishes;
    if (fread(&numOfClownFishes, sizeof(int), 1, file) != 1) {
        printf("Failed to read the number of clown fishes from the file!\n");
        return NULL;
    }

    // Read clown fishes
    for (int i = 0; i < numOfClownFishes; i++) {
        ClownFish* clownFish = readClownFishFromBinaryFile(file);
        addClownFish(salt, clownFish);
    }

    return salt;
}
void freeSaltAquarium(SaltAquarium* aquarium) {
    //Using free general function(void*)
    if (aquarium != NULL) {
        if (aquarium->sharks != NULL) {
            freeArr((void**)aquarium->sharks, aquarium->numSharks, free);
        }

        if (aquarium->clownFishes != NULL) {
            freeArr((void**)aquarium->clownFishes, aquarium->numClownFishes, free);
        }

        if (aquarium->seaCreatures != NULL) {
            freeArr((void**)aquarium->seaCreatures, aquarium->numSeaCreatures, free);
        }

        free(aquarium);
    }
}

//-------------------------------Printings------------------------------------//
void printSeaCreature(const void* creature) {
    const SeaCreature* seaCreature = (const SeaCreature*)creature;

    if (seaCreature == NULL) {
        printf("Error: Null sea creature pointer passed to printSeaCreature.\n");
        return;
    }

    printf("Age : {%d} , Life Span : {%d} , Color 1 : {%s} , Color 2 : {%s}\n",
        seaCreature->age,
        seaCreature->lifeSpan,
        (seaCreature->color1 >= 0 && seaCreature->color1 < eNofSeaCreatureColors) ? SeaCreatureColour[seaCreature->color1] : "Unknown",
        (seaCreature->color2 >= 0 && seaCreature->color2 < eNofSeaCreatureColors) ? SeaCreatureColour[seaCreature->color2] : "Unknown");
}

void printShark(const void* shark) {
    const Shark* sharkObj = (const Shark*)shark;

    if (sharkObj == NULL) {
        printf("Error: Null shark pointer passed to printShark.\n");
        return;
    }

    printf("Name : {%s} , Age : {%d} , Life Span : {%d} , Color 1 : {%s} , Color 2 : {%s} , Weight : {%.2lf}\n",
        sharkObj->name,
        sharkObj->seaCreature.age,
        sharkObj->seaCreature.lifeSpan,
        (sharkObj->seaCreature.color1 >= 0 && sharkObj->seaCreature.color1 < eNofSeaCreatureColors) ? SeaCreatureColour[sharkObj->seaCreature.color1] : "Unknown",
        (sharkObj->seaCreature.color2 >= 0 && sharkObj->seaCreature.color2 < eNofSeaCreatureColors) ? SeaCreatureColour[sharkObj->seaCreature.color2] : "Unknown",
        sharkObj->weight);
}


void printClownFish(const void* clownFish) {
    const ClownFish* clownFishObj = (const ClownFish*)clownFish;

    if (clownFishObj == NULL) {
        printf("Error: Null clown fish pointer passed to printClownFish.\n");
        return;
    }

    printf("Name : {%s} , Age : {%d} , Life Span : {%d} , Color 1 : {%s} , Color 2 : {%s}\n",
        clownFishObj->name,
        clownFishObj->seaCreature.age,
        clownFishObj->seaCreature.lifeSpan,
        (clownFishObj->seaCreature.color1 >= 0 && clownFishObj->seaCreature.color1 < eNofSeaCreatureColors) ? SeaCreatureColour[clownFishObj->seaCreature.color1] : "Unknown",
        (clownFishObj->seaCreature.color2 >= 0 && clownFishObj->seaCreature.color2 < eNofSeaCreatureColors) ? SeaCreatureColour[clownFishObj->seaCreature.color2] : "Unknown");
}
