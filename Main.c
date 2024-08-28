#include <stdio.h>
#include <stdlib.h>
#include "Dolphin.h"
#include "ClownFish.h"
#include "generalFunctions.h"
#include "SeaCreatures.h"
#include "Shark.h"

#include "ChildFish.h"
#include <stdio.h>
#include "CentralAquarium.h"
#include "SaltAquarium.h"



CentralAquarium* createOurAquarium() {
    CentralAquarium* myAquarium = initCentralAquarium("Our Aquarium");
    Dolphin* dolphin1 = createDolphin(11, 5.3, 'A');
    Dolphin* dolphin2 = createDolphin(20, 6.1, 'B');
    Dolphin* dolphin3 = createDolphin(10, 4.9, 'C');
    Dolphin* dolphin4 = createDolphin(12, 7.11, 'D');
    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin1);
    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin2);
    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin3);
    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin4);

    FreshFish* freshFish1 = createFreshFish(10, 5, "fresh1");
    FreshFish* freshFish2 = createFreshFish(10, 5, "fresh2");
    ChildFish* childFish_1_2 = createChildFIsh(1, freshFish1, freshFish2);
    addFreshFish(myAquarium->freshAquarium, freshFish1, freshFish2);
    FreshFish* freshFish3 = createFreshFish(7, 5, "fresh3");
    FreshFish* freshFish4 = createFreshFish(7, 5, "fresh4");
    ChildFish* childFish_3_4 = createChildFIsh(2, freshFish3, freshFish4);
    addFreshFish(myAquarium->freshAquarium, freshFish3, freshFish4);

    SeaCreature* seaCreature1 = createSeaCreature(8, 10, 1, 2);
    SeaCreature* seaCreature2 = createSeaCreature(3, 8, 3, 4);
    addSeaCreature(myAquarium->saltAquarium, seaCreature1);
    addSeaCreature(myAquarium->saltAquarium, seaCreature2);

    Shark* shark1 = createShark("MommyShark", 700.0, 7, 12, 2, 4);
    Shark* shark2 = createShark("DaddyShark", 1500.0, 10, 30, 0, 3);
    addShark(myAquarium->saltAquarium, shark1);
    addShark(myAquarium->saltAquarium, shark2);

    ClownFish* clownFish1 = createClownFish("Nemo1", 2, 4, 1, 2);
    ClownFish* clownFish2 = createClownFish("Nemo2", 5, 8, 3, 4);
    addClownFish(myAquarium->saltAquarium, clownFish1);
    addClownFish(myAquarium->saltAquarium, clownFish2);

    addRandomFish(myAquarium->freshAquarium, createRandomFish());
    addRandomFish(myAquarium->freshAquarium, createRandomFish());
    addRandomFish(myAquarium->freshAquarium, createRandomFish());


    return myAquarium;
}

int main(void) {
    CentralAquarium* aquarium = createOurAquarium();

    int choice;
    do {
        printf("\n--- Aquarium Management System ---\n");
        printf("1.  Print Central Aquarium\n");
        printf("2.  Write Aquarium to text file\n");
        printf("3.  Read Aquarium from text file\n");
        printf("4.  Write Aquarium to binary file\n");
        printf("5.  Read Aquarium from binary file\n");
        printf("6.  Add a dolphin\n");
        printf("7.  Search dolphin by name\n");
        printf("8.  Remove dolphin by friendship value\n");
        printf("9.  Add a sea creature\n");
        printf("10. Age all saltAquarium sea creatures\n");
        printf("11. Add a shark\n");
        printf("12. Sort salt Aquarium sharks by criteria\n");
        printf("13. Search salt Aquarium sharks by criteria\n");
        printf("14. Add a clown fish\n");
        printf("15. Add a fresh fish\n");
        printf("16. Add a child fish\n");
        printf("17. Add a random fish\n");
        printf("18. Find the oldest fresh fish in the aquarium\n");
        printf("19. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            printAllCentralAuqruaiumDetails(aquarium);
            break;
        }
        case 2: {
            writeCentralAquariumToTxtFile(aquarium, "test.txt");
            printf("Write to file successfully\n");
            break;
        }
        case 3: {
            aquarium = readCentralAquariumFromTxtFile("test.txt");
            printAllCentralAuqruaiumDetails(aquarium);
            break;
        }
        case 4: {
            writeCentralAquariumToBinnaryFile(aquarium, "test.bin");
            break;
        }
        case 5: {
            aquarium = readCentralAquariumFromBinnaryFile("test.bin");
            break;
        }
        case 6: {
            // Update dolphin list with the returned value from getDolphinFromUser
            aquarium->freshAquarium->dolphinLinkedList = getDolphinFromUser(aquarium->freshAquarium->dolphinLinkedList);
            break;
        }
        case 7: {
            clearInputBuffer();
            char tav;
            printf("Please enter one character: ");
            scanf("%c", &tav);
            Dolphin* result = searchDolphinByName(tav, aquarium->freshAquarium->dolphinLinkedList);
            if (result == NULL) {
                printf("No dolphin found\n");
            }
            else {
                printDolphin(result);
            }
            break;
        }
        case 8: {

            removeAndPrintChangesInDolphinsList(&(aquarium->freshAquarium->dolphinLinkedList));

            break;
        }
        case 9: {
            getSeaCreatureFromUser(aquarium->saltAquarium);
            break;
        }
        case 10: {
            ageAllSeaCreatures(aquarium->saltAquarium);
            ageAllSharks(aquarium->saltAquarium);
            ageAllClownFishes(aquarium->saltAquarium);
            break;
        }
        case 11: {
            getSharkFromUser(aquarium->saltAquarium);
            break;
        }
        case 12: {
            sortSharksMenu(aquarium->saltAquarium);
            break;
        }
        case 13: {
            sharkSearchMenu(aquarium->saltAquarium);
            break;
        }
        case 14: {
            initClownFish(aquarium->saltAquarium);
            break;
        }
        case 15: {
            FreshFish* newFreshFish1 = createFreshFishFromUser();
            FreshFish* newFreshFish2 = createFreshFishFromUser();
            if (newFreshFish1 != NULL) {
                addFreshFish(aquarium->freshAquarium, newFreshFish1, newFreshFish2);
                printf("Fresh fish added successfully!\n");
            }
            else {
                printf("Failed to create fresh fish.\n");
            }
            break;
        }
        case 16: {
            FreshFish* f1 = createFreshFishFromUser();
            FreshFish* f2 = createFreshFishFromUser();
            printf("Enter number of child: ");
            int numOfChild = 0;
            scanf("%d", &numOfChild);
            ChildFish* child = createChildFIsh(numOfChild, f1, f2);
            addFreshFish(aquarium->freshAquarium, f1, f2);
            break;
        }
        case 17: {
            RandomFish* newRandomFish = createRandomFish();
            if (newRandomFish != NULL) {
                addRandomFish(aquarium->freshAquarium, newRandomFish);
                printf("Random fish added successfully!\n");
            }
            else {
                printf("Failed to create random fish.\n");
            }
            break;
        }
        case 18: {
            findOldestFish(aquarium->freshAquarium->freshFish, aquarium->freshAquarium->freshFishSize);
            break;
        }
        case 19: {
            // Free the aquarium and exit
            freeCentralAquarium(aquarium);
            printf("Thank you!\n");
            break;
        }
        }
    } while (choice != 19);

    return 0;
}
