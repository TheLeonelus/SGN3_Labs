#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int arrayFullfill(char* string);
void wordOccurCount (char* string, int length);

int main()
{
    char *string = (char*) malloc(sizeof(char));
    int length = arrayFullfill(string);
    wordOccurCount(string, length);

    return EXIT_SUCCESS;
}

int arrayFullfill(char* string)
{
    char c = getchar();
    int length = 1, a = c;
    while (a != 10) { // Проверка на символ LF
        *(string + length - 1) = tolower(c);
        length++;
        string = (char*) realloc(string, length);
        c = getchar();
        a = c;
    }
    *(string + length) = '\0';
    return length;
}

void wordOccurCount (char* string, int length)
{
    char **wordArray = (char **) malloc(sizeof(char *));
    int *wordCount = (int *) calloc(1, sizeof(int));
    *wordArray = (char *) malloc(sizeof(char));
    int i = 0, uniqueWordsCount = 0;
    while(*(string + i) != '\0') {
        int bufferPosition = 0;
        while((*(string + i + bufferPosition) != ' ')||(*(string + i + bufferPosition) != '\0'))
            bufferPosition++;
        i+=bufferPosition;
        char* bufferString = (char *) malloc(bufferPosition*sizeof(char));
        for (int j = 0; j < bufferPosition; j++)
            strcpy(bufferString + j, string + i + j);
        *(bufferString + bufferPosition) = '\0';
        int l = 0, check = 0;
        do {
            char* entry = strstr(*(string + i), *(wordArray + l));
            if(entry == 0) {
                *(wordCount + l) += 1;
                check = 0;
                break;
            }
            else
                check = 1;
            l++;
        } 
        while (l < uniqueWordsCount);
        if(check) {
            uniqueWordsCount++;
            wordArray = (char **) realloc(wordArray, uniqueWordsCount);
            *(wordArray + uniqueWordsCount) = malloc(bufferPosition*sizeof(char));
            *(wordArray + uniqueWordsCount) = 
        }
    }
}
// 9.1. Вводится текст. 
// Составить частотный словарь слов в тексте. 
// Слова в словаре не должны повторятся. 
// Выводить вертикальным списком, слева - слово, справа - кол-во повторений. (Учет регистра необязателен)
