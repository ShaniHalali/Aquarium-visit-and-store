#ifndef GENERAL_FUNCTION_H
#define GENERAL_FUNCTION_H
#include <stdio.h>
#pragma warning (disable:4996)
#include <stdlib.h>

void printArr(const void** arr, int size, void (*print)(const void*));
void clearInputBuffer();
int getValidAge();
int getValidLifeSpan(int age);
void writeDoubleToBinaryFile(double value, FILE* file);
double readDoubleFromBinaryFile(FILE* file);
#endif 
