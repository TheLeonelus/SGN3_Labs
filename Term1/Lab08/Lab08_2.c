#include "customstrings.h"

#include <stdio.h>
#include <stdlib.h>

#define SUFFIX_AMOUNT 2

int inputAmount();
int stringsFullfill(int amount, char ***arrayStrings);
void stringsReplaceSuffixes(int amount, char **arrayStrings, char **arraySuffixes);
void freeArray(int n, char **matrix);

int main()
{
    int amount = inputAmount();
    printf_s("\nInput strings..");
    char **arrayStrings = (char **) malloc(sizeof(char *) * amount);
    if (arrayStrings == NULL)
        return EXIT_FAILURE;
    if(stringsFullfill(amount, &arrayStrings))
        return EXIT_FAILURE;
    printf_s("\nInput suffixes..\n");
    char **arraySuffixes = (char **) malloc(sizeof(char *) * SUFFIX_AMOUNT);
    if (arraySuffixes == NULL)
        return EXIT_FAILURE;
    if(stringsFullfill(SUFFIX_AMOUNT, &arraySuffixes))
        return EXIT_FAILURE;
    stringsReplaceSuffixes(amount, arrayStrings, arraySuffixes);
    freeArray(amount, arrayStrings);
    freeArray(SUFFIX_AMOUNT, arraySuffixes);
    return EXIT_SUCCESS;
}

// Ввод количества строк для редактирования
int inputAmount()
{
    int check = 0;
    int n;
    do {
        printf_s("\nInput amount of strings: ");
        scanf_s("%d", &n);
        if (n <= 0)
            printf_s("\nInappropriate input! Please try again.");
        else
            check++;
    } while (check <= 0);
    getchar();
    return n;
}

// Функция выделения памяти | Не используется
void malloc_array(int n, char ***strArray)
{
    *strArray = (char **)malloc(sizeof(char *) * (n+1));
    if (*strArray != NULL) {
        for (int i = 0; i < n; i++) {
            *(*strArray + i) = (char *)malloc(sizeof(char) * (n+1));
            if (*(*strArray + i) == NULL) {
                for (i--; i >= 0; i--) {
                    free(*strArray + i);
                }
                free(*strArray);
                **strArray = NULL;
                break;
            }
        }
    }
}


// Динамическое выделение памяти и одновременное заполнение массива посимвольным чтением
int stringsFullfill(int amount, char ***array)
{
    for (int i = 0; i < amount; i++) {
        int length = 1;
        printf_s("\nString %d%s", i, ": ");
        *(*array + i) = (char *) malloc(sizeof(char)*length);
        if(*(*array +i) == NULL)
            return EXIT_FAILURE;
        if(arrayFullfill(*(*array + i)))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// Функция нахождения подстроки, её удаления и вставки новой
void stringsReplaceSuffixes(int amount, char **arrayStrings, char **arraySuffixes)
{
    int strSufLength = strlen(*arraySuffixes), strInsLength = strlen(*(arraySuffixes + 1));
    for (int i = 0; i < amount; i++) {
        int j = 0;
        while (1) {
            char* entry = strstr(*(arrayStrings + i), *arraySuffixes);
            if(entry==NULL)
                break;
            int position = entry - *(arrayStrings + i);
            strcpy(*(arrayStrings + i) + position, *(arrayStrings + i) + position + strSufLength);
            strins(*(arrayStrings + i) + position, *(arraySuffixes + 1));
        }
        printf_s("\n Modified string: \"%s\"\n", *(arrayStrings + i));
    }
}

// Очищение памяти двумерного массива
void freeArray(int n, char **matrix)
{
    for (int i = 0; i < n; i++)
        free(*(matrix + i));
    free(matrix);
}

/*
8.2. Задается массив строк. Каждая строка включает в себя Фамилию Имя Отчество.
Задается две строки (суффиксы) (например, "ov" "idze" или "chuk" "ko") suf1 и suf2. Заменяем все вхождения suf1 в фамилии на suf2.
*/