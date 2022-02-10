#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "functions.h"

// Перемещает курсор на заданную позицию
void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

// Возвращает размер файла в байтах
int getFileSizeInBytes(FILE* f)
{
    int position = ftell(f);
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, position * sizeof(game), SEEK_SET);
    return size;
}

// Возвращает количество элементов в файле
int getElementsCount(FILE* f)
{
    return getFileSizeInBytes(f) / sizeof(game);
}

// Устанавливает новый размер файла
void setFileSize(FILE* f, long newSize)
{
    int fileDescriptor = _fileno(f);
    chsize(fileDescriptor, newSize);
}

// Записывает переданную структуру в файл
void writeElementInFile(FILE* f, const game game, int index)
{
    fseek(f, sizeof(game) * index, SEEK_SET);
    fwrite(&game, sizeof(game), 1, f);
    fflush(f);
    rewind(f);
}

// Считывает элемент по указанному индексу
game readElementFromFile(FILE* f, int index)
{
    fseek(f, sizeof(game) * index, SEEK_SET);
    game result;
    fread(&result, sizeof(game), 1, f);
    rewind(f);
    return result;
}

// Утилитарная функция перестановки двух элементов в файле
void swapRecordsInFile(FILE* f, int index1, int index2)
{
    game rec1 = readElementFromFile(f, index1);
    game rec2 = readElementFromFile(f, index2);
    writeElementInFile(f, rec1, index2);
    writeElementInFile(f, rec2, index1);
}

// Компаратор по имени
int compareByName(game record1, game record2)
{
    return strcmp(record1.name, record2.name);
}

// Компаратор по разработчику
int compareByDeveloper(game record1, game record2)
{
    return strcmp(record1.developer, record2.developer);
}

// Компаратор по издателю
int compareByPublisher(game record1, game record2)
{
    return strcmp(record1.publisher, record2.publisher);
}

// Компаратор по рейтингу
int compareByRating(game record1, game record2)
{
    return record1.rating > record2.rating;
}