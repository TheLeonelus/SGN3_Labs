#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 6031)
#endif

#include "utility.h"

// Функция основного меню
int menuInOut()
{
    system("clear");
    printf_s("\n================================================================="
        "\n=                             [Menu]                            ="
        "\n================================================================="
        "\n= 1. Add new element.                                           ="
        "\n= 2. Print all elements.                                        ="
        "\n= 3. Sort (in ascending order) all elements by specified field. ="
        "\n= 4. Delete specific element.                                   ="
        "\n= 5. Exit.                                                      ="
        "\n================================================================="
        "\n= Input:                                                        ="
        "\n=================================================================\033[11;10H"); // \033[%;%H - ANSI cursor escape sequence
    int choice;
    while (1)
    {
        scanf("%i", &choice); // Возможно ли игнорировать буквы и т.п.?
        if ((choice > 5) || (choice < 1)) {
            printf_s("\033[11;10H\033[K"); // \033[K - ANSI erase escape sequence
            printf_s("\033[11;10H                                                       =");
            printf_s("\033[11;10HInappropriate input! Try Again please.");
            Sleep(1500);
            printf_s("\033[11;10H                                                       =\033[11;10H");
        }
        else
            break;
    };
    printf_s("\033[13;1H");
    return choice;
}

// Возвращает заполненную структуру из stdout
game structInput()
{
    game temp;
    printf_s("\n\n=====[Input information]=====");
    printf_s("\n\nInput Name: ");
    getchar();
    fgets(temp.name, MAX_SIZE, stdin);
    *(temp.name + strcspn(temp.name, "\r\n")) = '\0'; 
    *temp.name = toupper(*temp.name);
    printf_s("\nInput Developer: ");
    fgets(temp.developer, MAX_SIZE, stdin);
    *(temp.developer + strcspn(temp.developer, "\r\n")) = '\0';
    *temp.developer = toupper(*temp.developer);
    printf_s("\nInput Publisher: ");
    fgets(temp.publisher, MAX_SIZE, stdin);
    *(temp.publisher + strcspn(temp.publisher, "\r\n")) = '\0';
    *temp.publisher = toupper(*temp.publisher);
    while (1) {
        printf_s("\nInput rating by 100 grade: ");
        scanf("%i", &temp.rating);
        if (temp.rating <= 0 || temp.rating > 100)
            printf_s("\nInappropriate input! Please try again.\n");
        else
            break;
    }
    printf_s("\n\n=============================");
    Sleep(250);
    return temp;
}

// Записывает в конец файла структуру из stdout
int structWriteInFile(FILE* f)
{
    f = fopen("file.txt", "a+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    game temp = structInput();
    fwrite(&temp, sizeof(game), 1, f);
    fflush(f);
    fclose(f);
    return EXIT_SUCCESS;
}

// Выводит все элементы файла
int filePrint(FILE *f)
{
    f = fopen("file.txt", "r+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    int count = getElementsCount(f);
    for (int i = 0; i < count; i++) {
        game record = readElementFromFile(f, i);
        printf_s("\n=====Element [#%i]=====", (i + 1));
        printf_s("\n= Game: %s", record.name);
        printf_s("\n= Developer: %s", record.developer);
        printf_s("\n= Publisher: %s", record.publisher);
        printf_s("\n= Rating: %i", record.rating);
        printf_s("\n======================\n");
    }
    fclose(f);
    return EXIT_SUCCESS;
}

// Меню выбора поля для сортировки
int fieldToSortChoose()
{
    int sortChoice;
    printf_s("\n================================"
        "\n=[Choose field to be sorted by]="
        "\n=1. Game                       ="
        "\n=2. Developer                  ="
        "\n=3. Publisher                  ="
        "\n=4. Rating                     ="
        "\n================================"
        "\n= Input:                       ="
        "\n================================\033[21;10H");
    while (1) {
        scanf("%i", &sortChoice);
        if ((sortChoice > 4) || (sortChoice < 1)) {
            printf_s("\033[21;10H\033[K"); // \033[K - ANSI erase escape sequence
            printf_s("\033[21;10H                      =");
            printf_s("\033[21;10HInappropriate input!");
            Sleep(1500);
            printf_s("\033[21;10H                      =\033[21;10H");
        }
        else
            break;
    }
    printf_s("\033[23;1H");
    return sortChoice;
}

// Удаляет указаный элемент из файла
int removeElementFromFile(FILE* f)
{
    f = fopen("file.txt", "r+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    int recordCount = getElementsCount(f);
    int index = 0;
    while (1) {
        printf_s("\nInput which element to delete: ");
        scanf("%i", &index);
        if (index > recordCount || index < 1)
            printf_s("\nInappropriate input!\n");
        else
            break;
    }
    index--;
    for (int i = index + 1; i < recordCount; i++)
    {
        game s = readElementFromFile(f, i);
        writeElementInFile(f, s, i - 1);
    }
    int newFileSize = (recordCount - 1) * sizeof(game);
    setFileSize(f, newFileSize);
    rewind(f);
    fclose(f);
    return EXIT_SUCCESS;
}

// Сортировка файла пузырем заданным компаратором
void sortFile(FILE* f, int (*cmp)(game record1, game record2))
{
    int count = getElementsCount(f);
    game record1;
    game record2;
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            record1 = readElementFromFile(f, i);
            record2 = readElementFromFile(f, j);

            if (cmp(record1, record2) == 1)
                swapRecordsInFile(f, i, j);
        }
    }
}

