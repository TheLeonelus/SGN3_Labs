#ifndef _ADDITONAL_FUNCTIONS
#define _ADDITIONAL_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <synchapi.h>
#include <string.h>
#include <conio.h>
#include <io.h>

#include "struct.h"

int menuInOut();
game structInput();
int structWriteInFile(FILE* f);
int filePrint(FILE* f);
int fieldToSortChoose();
int removeElementFromFile(FILE* f);
void sortFile(FILE* f, int (*cmp)(game record1, game record2));

#endif