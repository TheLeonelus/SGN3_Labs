#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 0.0000000001

void matrixInput(int *n, int *m);
void malloc_matrix(int n, int m, int **matrix);
void valuesInput(int n, int m, int **matrix);
void valuesOutput(int n, int m, int **matrix);
void matrixTransposition(int n, int m, int **matrix);
void maxToElementSummary(int n, int m, int **matrix);

int main(void)
{
    int n, m; // n - строки; m - столбцы
    matrixInput(&n, &m);
    int **matrix = malloc(sizeof(int*)*n);
    if(matrix!=NULL) {
        for(int i=0; i<n; i++) {
            *(matrix+i) = malloc(sizeof(int)*m);
            if(*(matrix+i)==NULL) {
                for(i--; i>=0; i--) {
                    free(matrix+i);
                }
                free(matrix);
                *matrix=NULL;
                break;
            }
        }
    }
    //malloc_matrix(n, m, &*matrix);
    valuesInput(n, m, &*matrix);
    printf_s("\n\nOriginal: \n");
    valuesOutput(n, m, &*matrix);
    maxToElementSummary(n, m, matrix);
    matrixTransposition(n, m, matrix);
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

void malloc_matrix(int n, int m, int **matrix)
{
    matrix = malloc(sizeof(int *) * n);
    if (matrix != NULL) {
        for (int i = 0; i < n; i++) {
            *(matrix + i) = malloc(sizeof(int) * m);
            if (*(matrix + i) == NULL) {
                for (i--; i >= 0; i--) {
                    free(matrix + i);
                }
                free(matrix);
                *matrix = NULL;
                break;
            }
        }
    }
}

void valuesInput(int n, int m, int **matrix)
{
    printf_s("\nInput array elements...");
    int element = 0;
    for (int i = 0; i < n; i++) {
        element++;
        for (int j = 0; j < m; j++) {
        //  printf_s("\nArray[%i%s%i%s", i, "][", j, "]: "); // Для самостоятельного заполнения
        //  scanf_s("%i", &*(*(matrix + i) + j));
            *(*(matrix + i) + j) = element; // Чтобы самостоятельно не заполнять
        //  printf_s("\nArray[%i%s%i%s%o", i, "][", j, "]: ", *(*(matrix + i) + j));
            element++;
        }
    }
}

void valuesOutput(int n, int m, int **matrix)
{
    printf_s("m | n ");
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

//6.1. Вводится матрица. Память выделять динамически. Транспонировать ее относительно побочной диагонали и вывести на экран.
//6.2.  Вводится матрица. Память выделять динамически.
//1 вар. Записать вместо max сумму элементов над побочной диагональю