#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <io.h>

char* removespaces(char* s);
char* strins(char* s, char* sub_s);
void writeToArrayFromFile(FILE* f, char* array);
char* numberingArray(char* array);
void writeArrayToFile(char* array, FILE* f);

int main()
{
    FILE* f = fopen("file.txt", "r+");
    if (!f) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    fseek(f, 0, SEEK_END);
    unsigned int size = ftell(f);
    rewind(f);
    char* array = (char*) malloc(sizeof(char) * (size + 1));
    if (array == NULL)
        return NULL;
    writeToArrayFromFile(f, array);
    if (array == NULL)
        return EXIT_FAILURE;
    fclose(f);
    removespaces(array); 
    printf("\n========\nString with removed spaces:\n\"%s\"\n========\n", array);
    numberingArray(array);
    writeArrayToFile(array, f);
    printf("\n========\nString numbered:\n\"%s\"\n========\n", array);
    free(array);
    return EXIT_SUCCESS;
}

// Удаление лишних пробелов и LF
char* removespaces(char* s)
{
    while (*s == ' ')
        strcpy(s, s + 1);
    unsigned int len = strlen(s);
    while (*(s + len - 2) == ' ') {
        *(s + len - 1) = '\0';
        len = strlen(s);
        if (*(s + len - 2) != ' ')
            *(s + len - 1) = '\0';
    }
    len = strlen(s);
    int j = 0;
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL)
        return NULL;
    for (int i = 0; i < len; i++) {
        if (*(s + i) == ' ') {
            if (*(s + i + 1) == ' ') continue;
        }
        if (*(s + i) == '\n') {
            if (*(s + i + 1) == '\n') continue;
        }
        *(result + j) = *(s + i);
        j++;
    }
    j++;
    *(result + j) = '\0';
    strcpy(s, result);
    free(result);
    return s;
}

// Вставка подстроки sub_s в строку s
char* strins(char* s, char* sub_s)
{
    unsigned int len = strlen(s);
    char* temp = malloc((len + 1)*sizeof(char));
    if (temp == NULL)
        return NULL;
    strcpy(temp, s);
    strcpy(s, sub_s);
    strcpy(s + strlen(sub_s), temp);
    free(temp);
    return s;
}

// Чтение текста из файла
void writeToArrayFromFile(FILE* f, char* array)
{
    int c, j = 0;
    printf_s("========\nOriginal string: \n\n\"");
    while ((c = fgetc(f)) != EOF) {
        *(array + j) = putchar(c);
        j++;
    }
    *(array + j) = '\0';
    printf("\"\n========\n");
}

// Пронумерование строк
char* numberingArray(char* s)
{
    unsigned int size = strlen(s), position = 0, i = 1;
    char* numberedList = (char*)malloc(4 * sizeof(char));
    if (numberedList == NULL)
        return NULL;
    sprintf(numberedList, "%i. \0", i);
    size += strlen(numberedList) + 1;
    strins(s, numberedList);
    i++;
    do {
        position += strcspn(s + position, "\n") + 1;
        int check = position;
        int check2 = size;
        if (position == size)
            break;
        size += strlen(numberedList);
        sprintf(numberedList, "%i. ", i);
        strins(s + position, numberedList);
        i++;
    } while (1);
    free(numberedList);
    return s;
}

// Запись строки в файл
void writeArrayToFile(char* s, FILE* f)
{
    f = fopen("output.txt", "w");
    int size = strlen(s);
    *(s + size - 1) = EOF;
    int j = 0;
    while (*(s + j) != EOF) {
        putc(*(s + j), f);
        j++;
    }
    fflush(f);
    fclose(f);
}