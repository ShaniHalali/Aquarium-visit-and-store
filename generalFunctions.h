#ifndef GENERAL_FUNCTION_H
#define GENERAL_FUNCTION_H
#include <stdio.h>

void printArr(const void** arr, int size, void (*print)(const void*));
void clearInputBuffer();
void writeDoubleToBinaryFile(double value, FILE* file);
double readDoubleFromBinaryFile(FILE* file);
#endif 
