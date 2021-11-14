#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "customstrings.h"

int inputSize();

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
    printf_s("\n\nOriginal string: %s", string);
    removespaces(string);
    printf_s("\nString with deleted spaces: %s\n", string);
    return EXIT_SUCCESS;
}
// No problem have been
// Условие Л.р.№8
// 8.1. Вводится строка. Удалить все лишние пробелы.
// 8.2. Задается массив строк. Каждая строка включает в себя Фамилию Имя Отчество.
// Задается две строки (суффиксы) (например, "ov" "idze" или "chuk" "ko") suf1 и suf2. Заменяем все вхождения suf1 в фамилии на suf2.
