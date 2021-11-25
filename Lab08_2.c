#include <stdio.h>
#include <stdlib.h>
#include "customstrings.h"

#define SUFFIX_AMOUNT 2

int inputAmount();
void stringsFullfill(int amount, char ***arrayStrings);
void stringsReplaceSuffixes(int amount, char **arrayStrings, char **arraySuffixes);
void freeArray(int n, char ***matrix);

int main()
{
    int amount = inputAmount();
    printf_s("\nInput strings..");
    char **arrayStrings = (char **) malloc(sizeof(char *) * (amount+1));
    if (arrayStrings == NULL)
        return EXIT_FAILURE;
    stringsFullfill(amount, &arrayStrings);
    printf_s("\nInput suffixes..\n");
    char **arraySuffixes = (char **) malloc(sizeof(char *) * (SUFFIX_AMOUNT+1));
    if (arraySuffixes == NULL)
        return EXIT_FAILURE;
    stringsFullfill(SUFFIX_AMOUNT, &arraySuffixes);
    stringsReplaceSuffixes(amount, arrayStrings, arraySuffixes);
    freeArray(amount, &arrayStrings);
    freeArray(SUFFIX_AMOUNT, &arraySuffixes);
    return EXIT_SUCCESS;
}

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

void stringsFullfill(int amount, char ***array)
{
    for (int i = 0; i < amount; i++) {
        int length = 1;
        printf_s("\nString %d%s", i, ": ");
        *(*array + i) = (char *) malloc(sizeof(char)*length);
        char c = getchar();
        int a = c;
        while (a != 10) { // Проверка на символ LF
            *(*(*array + i) + length - 1) = c;
            length++;
            *(*array + i) = (char *) realloc(*(*array + i), length);
            c = getchar();
            a = c;
        }
        *(*(*array + i) + length + 1) = '\0';
    }
}

void stringsReplaceSuffixes(int amount, char **arrayStrings, char **arraySuffixes)
{
    int strSufLength = strlen(*arraySuffixes), strInsLength = strlen(*(arraySuffixes + 1));
    for (int i = 0; i < amount; i++) {
        int j = 0;
        while (*(*(arrayStrings + i) + j) != ' ')
        {
            char* entry = strstr(*(arrayStrings + i), *arraySuffixes);
            int position = entry - *(arrayStrings + i);
            *(arrayStrings + i) += position;
            strcpy(*(arrayStrings + i), *(arrayStrings + i) + strSufLength);
            strins(*(arrayStrings + i), *(arraySuffixes + 1));
        }
        printf_s("\n STR: \"%s\"", *(arrayStrings + i));
    }
}

void freeArray(int n, char ***matrix)
{
    for (int i = 0; i < n; i++)
        free(*(*matrix + i));
    free(*matrix);
}
// 8.2. Задается массив строк. Каждая строка включает в себя Фамилию Имя Отчество.
// Задается две строки (суффиксы) (например, "ov" "idze" или "chuk" "ko") suf1 и suf2. Заменяем все вхождения suf1 в фамилии на suf2.