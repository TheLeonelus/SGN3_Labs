#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)
#endif

#include "functions.h"
#include "utility.h"

int main()
{
    FILE* f;
    f = fopen("file.txt", "r+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    fclose(f);
    int choice = menuInOut();
    while (choice != 5) {
        switch (choice) {
            case(1): {
                if (structWriteInFile(f))
                    return EXIT_FAILURE;
                break;
            }
            case(2): {
                if (filePrint(f))
                    return EXIT_FAILURE;
                printf_s("\nPress any key to proceed...");
                _getch();
                break;
            }
            case(3): {
                f = fopen("file.txt", "r+");
                if (!f) {
                    perror("File opening failed");
                    return EXIT_FAILURE;
                }
                int sortChoice = fieldToSortChoose();
                switch (sortChoice) {
                case 1: {
                    sortFile(f, compareByName);
                    break;
                }
                case 2: {
                    sortFile(f, compareByDeveloper);
                    break;
                }
                case 3: {
                    sortFile(f, compareByPublisher);
                    break;
                }
                case 4: {
                    sortFile(f, compareByRating);
                    break;
                }
                }
                filePrint(f);
                printf_s("\nPress any key to proceed...");
                _getch();
                fclose(f);
                break;
            }
            case(4): {
                if (filePrint(f))
                    return EXIT_FAILURE;
                if (removeElementFromFile(f))
                    return EXIT_FAILURE;
                if (filePrint(f))
                    return EXIT_FAILURE;
                break;
            }
        }
        choice = menuInOut();
    };
    return EXIT_SUCCESS;
}

/*
Часть 11.2.
Программа должна иметь меню с вариантами выбора действия: 
1 - Добавить в конец файла книгу/музыку/фильм 
2 - Вывести книги/музыку/фильмы на экран 
3 - Отсортировать книги/музыку/фильмы (по возрастанию по одному из полей) 
4 - Удалить книгу/музыку/фильм 
5 - Выход 

Для каждого действия открывать/закрывать файл с необходимыми флагами. 

Варианты: 
1 - Book. Удаление по автору, сортировка по ранку 
2 - Music. Удаление по исполнителю, сортировка по названию 
3 - Cinema. Удаление по режиссёру, сортировка по названию
*/