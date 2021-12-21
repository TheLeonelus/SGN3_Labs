#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *string = (char*) malloc(sizeof(char));
    char c = getchar();
    int length = 1, a = c;
    while (a != 10) { // Проверка на символ LF
        *(string + length - 1) = tolow(c);
        length++;
        string = (char*) realloc(string, length);
        c = getchar();
        a = c;
    }
    *(string + length) = '\0';
    int bufferPosition = 0;
    while(*(string + bufferPosition) != ' ')
        bufferPosition++;
    
    return EXIT_SUCCESS;
}

// 9.2. Вводится текст. 
// Вводится ширина. 
// Отформатировать текст по ширине. 
// Слова не разбивать, а переносить на новую строку целиком. 
// Недостающее пространство заполнять пробелами.