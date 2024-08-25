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