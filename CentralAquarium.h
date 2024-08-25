#include "FreshAquarium.h"
#include "SaltAquarium.h"

typedef struct CentralAquarium {

	FreshAquarium* freshAquarium;
	SaltAquarium* saltAquarium;
	char* name;
} CentralAquarium;


CentralAquarium* initCentralAquarium(char* name);

//Txt
CentralAquarium* readCentralAquariumFromTxtFile(char* fileName);
void writeCentralAquariumToTxtFile(CentralAquarium* ca, char* fileName);
//Binnary
void writeCentralAquariumToBinnaryFile(CentralAquarium* aquarium, char* fileName);
CentralAquarium* readCentralAquariumFromBinnaryFile(char* fileName);
void printAllCentralAuqruaiumDetails(CentralAquarium* aquarium);
void freeCentralAquarium(CentralAquarium* ca);

