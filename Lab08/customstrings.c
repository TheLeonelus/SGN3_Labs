#include <stdlib.h>
// Находит первое вхождение символа 'c' в строке 'str'
char *strchr(char *str, char c)
{
    char *p = str;
    for (; *p && *p != c; p++);
    return *p ? p : 0;
}

// Копирует 'source' в 'destination'
char* strcpy(char* destination, const char* source)
{
    if (destination == NULL)
        return NULL;
    char *ptr = destination;
        while (*source != '\0')
    {
    *destination = *source;
    destination++;
    source++;
    }
    *destination = '\0';
    return ptr;
}

// Вставляет 'sub_s' в 's'
int strins(char *s, char *sub_s)
{
    char *temp = (char *)malloc(strlen(s) + 1);
    if(temp == NULL)
        return EXIT_FAILURE;
    strcpy(temp, s);
    strcpy(s, sub_s);
    strcpy(s + strlen(sub_s), temp);
    free(temp);
    return EXIT_SUCCESS;
}

// Рассчитывает длину строки
unsigned int strlen(const char *str)
{
    unsigned int len = 0;
    for (; *str != '\0'; len++, str++);
    return len;
}

// Возвращает 0, если 'X' и 'Y' одинаковы
int compare(const char *X, const char *Y)
{
    while (*X && *Y)
    {
        if (*X != *Y)
        {
            return 0;
        }

        X++;
        Y++;
    }

    return (*Y == '\0');
}

// Находит первое вхождение подстроки Y в строке X
char *strstr(char *X, char *Y)
{
    while (*X != ' ')
    {
        if ((*X == *Y) && compare(X, Y))
        {
            return X;
        }
        X++;
    }

    return NULL;
}