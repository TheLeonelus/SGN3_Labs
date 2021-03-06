#include <stdio.h>
#include <stdlib.h>

void matrixInput(int *n, int *m);
void malloc_matrix(int n, int m, int ***matrix);
void valuesInput(int n, int m, int **matrix);
void valuesOutput(int n, int m, int **matrix);
void matrixTransposition(int n, int m, int **matrix);
void maxToElementSummary(int n, int m, int **matrix);
void freeMatrix(int n, int***matrix);

int main(void)
{
    int n, m;
    matrixInput(&n, &m);
    int **matrix;
    malloc_matrix(n, m, &matrix);
    valuesInput(n, m, matrix);
    printf_s("\n\nOriginal: \n");
    valuesOutput(n, m, matrix);
    maxToElementSummary(n, m, matrix);
    matrixTransposition(n, m, matrix);
    freeMatrix(n, &matrix);
    return EXIT_SUCCESS;
}

void matrixInput(int *n, int *m)
{
    int k = 0;
    while (k < 1) {
        printf_s("\nInput amount of lines: ");
        scanf_s("%i", &*n);
        printf_s("\nInput amount of columns: ");
        scanf_s("%i", &*m);
        if ((*n <= 0) || (*m <= 0))
            printf_s("\nInappropriate Input! Please try again.");
        else
            k++;
    }
}

void malloc_matrix(int n, int m, int ***matrix)
{
    *matrix = (int**) malloc(sizeof(int *) * n);
    if (*matrix != NULL) {
        for (int i = 0; i < n; i++) {
            *(*matrix + i) = (int*) malloc(sizeof(int) * m);
            if (*(*matrix + i) == NULL) {
                for (i--; i >= 0; i--) {
                    free(*matrix + i);
                }
                free(*matrix);
                **matrix = NULL;
                break;
            }
        }
    }
}

void valuesInput(int n, int m, int **matrix)
{
    printf_s("\nInput array elements...");
    char caseVariant;
    int k = 0;
    while(k < 1) {
    printf_s("\nDo you would like to fullfill array yourself? [Y/N]: ");
    scanf_s("%s", &caseVariant);
    if (caseVariant == 'N')
        k = 1;
    if (caseVariant == 'Y')
        k = 2;
    }
    if(k == 1) {
        int element = 0;
        for (int i = 0; i < n; i++) {
            element++;
            for (int j = 0; j < m; j++) {
                *(*(matrix + i) + j) = element;
                element++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf_s("\nArray[%i%s%i%s", i, "][", j, "]: ");
                scanf_s("%i", &*(*(matrix + i) + j));
            }
        }
    }
}

void valuesOutput(int n, int m, int **matrix)
{
    printf_s("n | m ");
    for (int i = 0; i < m; i++) {
        printf_s(" %1.1i%s", i, "     ");
    }
    printf_s("\n  |");
    for (int i = 0; i < m; i++) {
        printf_s("-------");
    }
    for (int i = 0; i < n; i++) {
        printf_s("\n  |\n%i%s", i, " |");
        for (int j = 0; j < m; j++) {
            printf_s("  %4.i%s", *(*(matrix + i) + j), " ");
        }
    }
}

void matrixTransposition(int n, int m, int **matrix)
{
    for (int i = 0; i < (n - 1); i++) {
        for (int j = 0; (i + j) < (n - 1); j++) {
            int bufferValue = *(*(matrix + i) + j);
            *(*(matrix + i) + j) = *(*(matrix + n - 1 - j) + m - 1 - i);
            *(*(matrix + n - 1 - j) + m - 1 - i) = bufferValue;
        }
    }
    printf_s("\n\nTranspositioned: \n");
    valuesOutput(n, m, matrix);
}

void maxToElementSummary(int n, int m, int **matrix)
{
    int elementSummary = 0;
    for (int i = 0; i < (n - 1); i++) {
        for (int j = 0; (i + j) < (n - 1); j++) {
            elementSummary += *(*(matrix + i) + j);
        }
    }
    int Column, Line, maxValue = **matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(*(*(matrix + i) + j) > maxValue) 
                maxValue = *(*(matrix + i) + j);
                Column = j;
                Line = i;
        }
    }
    int bufferValue = *(*(matrix + Line) + Column);
    *(*(matrix + Line) + Column) = elementSummary;
    printf_s("\n\nMaximum value replaced with element summary:\n");
    valuesOutput(n, m, matrix);
    *(*(matrix + Line) + Column) = bufferValue;
}

void freeMatrix(int n, int***matrix)
{
    for (int i = 0; i < n; i++)
        free(*(*matrix + i));
    free(*matrix);
}

//6.1. ???????????????? ??????????????. ???????????? ???????????????? ??????????????????????. ?????????????????????????????? ???? ???????????????????????? ???????????????? ?????????????????? ?? ?????????????? ???? ??????????.
//6.2.  ???????????????? ??????????????. ???????????? ???????????????? ??????????????????????.
//1 ??????. ???????????????? ???????????? max ?????????? ?????????????????? ?????? ???????????????? ????????????????????