#include "CentralAquarium.h"

void writeCentralAquariumToTxtFile(CentralAquarium* aquarium, char* fileName) {
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		printf("Failed to open file for writing!\n");
		return 1;
	}
	fprintf(file, "%s\n", aquarium->name);
	writeFreshAquariumToTxtFile(aquarium->freshAquarium, file);
	writeSaltAquariumToTxtFile(aquarium->saltAquarium, file);
	fclose(file);
}


void writeCentralAquariumToBinnaryFile(CentralAquarium* aquarium, char* fileName) {
	FILE* file = fopen(fileName, "wb");
	if (file == NULL) {
		printf("Failed to open file for writing!\n");
		return;
	}

	int nameLength = strlen(aquarium->name);
	fwrite(&nameLength, sizeof(int), 1, file);
	fwrite(aquarium->name, sizeof(char), nameLength, file);
	writeFreshAquariumToBinaryFile(aquarium->freshAquarium, file);
	writeSaltAquariumToBinaryFile(aquarium->saltAquarium, file);
	fclose(file);
}

CentralAquarium* readCentralAquariumFromBinnaryFile(char* fileName) {
	FILE* file = fopen(fileName, "rb");
	if (file == NULL) {
		printf("Failed to open file for reading!\n");
		return NULL;
	}

	// Allocate memory for CentralAquarium
	CentralAquarium* result = (CentralAquarium*)calloc(1, sizeof(CentralAquarium));

	int nameLength;
	if (fread(&nameLength, sizeof(int), 1, file) != 1) {
		printf("Failed to read aquarium name length from file!\n");
		fclose(file);
		free(result);
		return NULL;
	}
	result->name = (char*)calloc(nameLength + 1, sizeof(char));
	if (result->name == NULL) {
		printf("Memory allocation failed\n");
		fclose(file);
		free(result);
		return NULL;
	}
	if (fread(result->name, sizeof(char), nameLength, file) != nameLength) {
		printf("Failed to read aquarium name from file!\n");
		fclose(file);
		free(result->name);
		free(result);
		return NULL;
	}
	result->name[nameLength] = '\0';
	result->freshAquarium = readFreshAquariumFromBinaryFile(file);
	result->saltAquarium = readSaltAquariumFromBinaryFile(file);
	fclose(file);
	return result;


}



//CentralAquarium* readCentralAquariumFromTxtFile(char* fileName) {
//	FILE* file = fopen(fileName, "r");
//	if (file == NULL) {
//		printf("Failed to open file for reading!\n");
//		return NULL;
//	}
//	CentralAquarium* result = (CentralAquarium*)calloc(1, sizeof(CentralAquarium));
//	result->name = (char*)calloc(255, sizeof(char));
//	if (fscanf(file, "%s", result->name) != 1) {
//		printf("Failed to read aquarium name from file!\n");
//		fclose(file);
//		return NULL;
//	}
//	result->freshAquarium = readFreshAquariumFromFile(file);
//	result->saltAquarium = readSaltAquariumFromFile(file);
//	return result;
//}
CentralAquarium* readCentralAquariumFromTxtFile(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Failed to open file for reading!\n");
		return NULL;
	}

	CentralAquarium* result = (CentralAquarium*)calloc(1, sizeof(CentralAquarium));
	if (result == NULL) {
		printf("Memory allocation failed!\n");
		fclose(file);
		return NULL;
	}

	result->name = (char*)calloc(MAX_NAME_LENGTH, sizeof(char));
	if (result->name == NULL) {
		printf("Memory allocation for name failed!\n");
		free(result);
		fclose(file);
		return NULL;
	}

	// Read the entire line for the name including spaces
	if (fgets(result->name, MAX_NAME_LENGTH, file) == NULL) {
		printf("Failed to read aquarium name from file!\n");
		free(result->name);
		free(result);
		fclose(file);
		return NULL;
	}

	// Remove the newline character at the end if it exists
	size_t len = strlen(result->name);
	if (len > 0 && result->name[len - 1] == '\n') {
		result->name[len - 1] = '\0';
	}

	// Read other parts of the CentralAquarium
	result->freshAquarium = readFreshAquariumFromFile(file);
	result->saltAquarium = readSaltAquariumFromFile(file);

	fclose(file);
	return result;
}
void printAllCentralAuqruaiumDetails(CentralAquarium* aquarium) {
	printf("The aquarium data read from the text file :  \n");
	printf("\nAquarium name : %s \n", aquarium->name);
	
	if (aquarium->freshAquarium != NULL) {
		printAllFreshAquariums(aquarium->freshAquarium);
	}
	if (aquarium->saltAquarium != NULL) {
		printAllSaltAquariums(aquarium->saltAquarium);
	}
}

CentralAquarium* initCentralAquarium(char* name) {
	CentralAquarium* result = (CentralAquarium*)calloc(1, sizeof(CentralAquarium));
	result->name = name;
	result->freshAquarium = initFreshAquarium();
	result->saltAquarium = initSaltAquarium();
	return result;
}
void freeCentralAquarium(CentralAquarium* ca) {
	if (ca != NULL) {
		// Free FreshAquarium
		if (ca->freshAquarium != NULL) {
			freeFreshAquarium(ca->freshAquarium);
		}

		// Free SaltAquarium
		if (ca->saltAquarium != NULL) {
			freeSaltAquarium(ca->saltAquarium);
		}

		// Free name
		if (ca->name != NULL) {
			free(ca->name);
		}

		// Free CentralAquarium itself
		free(ca);
	}
}
