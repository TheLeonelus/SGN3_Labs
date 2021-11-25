#include <stdio.h>
#include <stdlib.h>
#include "customstrings.h"

int inputSize();
char* removespaces(char *s);

int main()
{
    char *string = (char*) malloc(sizeof(char));
    printf_s("\nWrite the string: ");
    char c = getchar();
    int length = 1, a = c;
    while (a != 10) { // Проверка на символ LF
        *(string + length - 1) = c;
        length++;
        string = (char*) realloc(string, length);
        c = getchar();
        a = c;
    }
    int len = strlen(string);
    *(string + length) = '\0';
    len = strlen(string);
    printf_s("\n\nOriginal string: \"%s\"", string);
    char* result = removespaces(string);
    printf_s("\nString with deleted spaces: \"%s\"\n", result);
    free(string);
    free(result);
    return EXIT_SUCCESS;
}

char* removespaces(char *s)
{
    char *p;
    while (*s == ' ')
        strcpy(s, s + 1);
    int len = strlen(s);
    while (*(s + len - 2) == ' ') {
        *(s + len - 1) = '\0';
        len = strlen(s);
        if(*(s + len - 2) != ' ')
            *(s + len - 1) = '\0';
    }
    len = strlen(s);
    int i = 0, j = 0;
    char* result = (char*) malloc((len+1)*sizeof(char));
    for (; i < len; i++) {
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
