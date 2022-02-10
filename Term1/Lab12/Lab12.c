#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)
#endif

#include "functions.h"
#include "utility.h"

// #define // для 1, 2, 3, 4, 5 выбора

int main()
{
    FILE* f;
    f = fopen("file.bin", "r+b");
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
                f = fopen("file.bin", "r+b");
                if (!f) {
                    perror("File opening failed");
                    return EXIT_FAILURE;
                }
                int sortChoice = fieldToSortChoose();
                switch (sortChoice) { // вынести
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
Такая же, что 11.2 (вторая часть 11 л.р.), только на бинарных файлах. 
Состоит из 2-х частей

Все действия должны выполняться напрямую на файлах, без выгрузки в оперативную память.
Необходимо написать шаблонные функции-помощники, как мы делали на семинарах и лекциях и работать с файлом как с массивом.
Для сортировки следует использовать функцию-компаратор.

12.1. Первая часть
1 и 2 пункты меню.
1 - Добавить в конец файла книгу/музыку/фильм
2 - Вывести книги/музыку/фильмы на экран

12.2. Вторая часть
3 и 4 пункты меню.
3 - Отсортировать книги/музыку/фильмы (по возрастанию по двум любым полям)
4 - Удалить книгу/музыку/фильм

Варианты:

1 - Book. Удаление по автору, сортировка по ранку и названию 
2 - Music. Удаление по исполнителю, сортировка по ранку и названию 
3 - Cinema. Удаление по режиссеру, сортировка по ранку и названию

Примечание: 
можно выбрать любую другую интересующую тематику, сопоставимую с примерами вариантов. Минимальное кол-во полей в структуре: 4
*/