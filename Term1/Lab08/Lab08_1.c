#include "customstrings.h"

#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h>

char* removespaces(char *s);

int main()
{
    char *string = malloc(sizeof(char));
        if(string == NULL)
    return EXIT_FAILURE;
    printf_s("\nWrite the string: ");
    char c = getchar();
    if(arrayFullfill(string))
        return EXIT_FAILURE;
    printf_s("\n\nOriginal string: \"%s\"", string);
    char* result = removespaces(string);
    if(result == NULL)
        return EXIT_FAILURE;
    printf_s("\nString with deleted spaces: \"%s\"\n", result);
    free(string);
    free(result);
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

// Функция удаления лишних пробелов
char* removespaces(char *s)
{
    char *p;
    while (*s == ' ') // Удаление пробелов в начале
        strcpy(s, s + 1);
    int len = strlen(s);
    while (*(s + len - 2) == ' ') { // Удаление пробелолв в конце
        *(s + len - 1) = '\0';
        len = strlen(s);
        if(*(s + len - 2) != ' ')
            *(s + len - 1) = '\0';
    }
    len = strlen(s);
    int i = 0, j = 0;
    char* result = malloc((len+1)*sizeof(char));
    if(result == NULL)
        return NULL;
    for (; i < len; i++) { // Удаление лишних пробелов между словами
        if (*(s + i) == ' ') {
            if (*(s + i + 1) == ' ') continue;
        }
        *(result + j) = *(s + i);
        j++;
    }
    j++;
    *(result + j) = '\0';
    return result;
}
// No problem have been
// Условие Л.р.№8
// 8.1. Вводится строка. Удалить все лишние пробелы.
