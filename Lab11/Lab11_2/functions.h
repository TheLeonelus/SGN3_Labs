#ifndef _ADDITONAL_FUNCTIONS
#define _ADDITIONAL_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <synchapi.h>
#include <string.h>
#include <conio.h>
#include <io.h>

#define MAX_SIZE 30

typedef struct game
{
    char name[MAX_SIZE];
    char developer[MAX_SIZE];
    char publisher[MAX_SIZE];
    int rating;
}game;

void gotoxy(int x, int y);
int menuInOut();
game structInput();
int structWriteInFile(FILE* f);
int filePrint(FILE* f);
int fieldToSortChoose();
int getFileSizeInBytes(FILE* f);
int getElementsCount(FILE* f);
void setFileSize(FILE* f, long newSize);
game readElementFromFile(FILE* f, int index);
void writeElementInFile(FILE* f, const game student, int index);
int removeElementFromFile(FILE* f);
int compareByName(game record1, game record2);
int compareByDeveloper(game record1, game record2);
int compareByPublisher(game record1, game record2);
int compareByRating(game record1, game record2);
void sortFile(FILE* f, int (*cmp)(game record1, game record2));
void swapRecordsInFile(FILE* f, int index1, int index2);
#endif