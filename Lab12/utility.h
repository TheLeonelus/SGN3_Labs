#ifndef _UTILITY_FUNCTIONS
#define _UTILITY_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <synchapi.h>
#include <string.h>
#include <conio.h>
#include <io.h>

#include "struct.h"

void gotoxy(int x, int y); // не выносить в header
int getFileSizeInBytes(FILE* f);
int getElementsCount(FILE* f);
void setFileSize(FILE* f, long newSize);
void writeElementInFile(FILE* f, const game student, int index); // вынести в gamefile.h
game readElementFromFile(FILE* f, int index);
void swapRecordsInFile(FILE* f, int index1, int index2);

#endif