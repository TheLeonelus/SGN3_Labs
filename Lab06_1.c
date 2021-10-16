#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 0.0000001

void matrixInput(int* n, int* m);
int** malloc_matrix(int n, int m, int** matrix);
void valuesInput(int n, int m, int** matrix);
void valuesOutput(int n, int m, int** matrix);
void matrixTransposition(int n, int m, int** matrix);

int main(void)
{
    int n,m; // n - строки; m - столбцы
    matrixInput(&n, &m);
    int** matrix = malloc(sizeof(int*)*n);
    if(matrix!=NULL)
    {
        for(int i=0; i<n; i++)
        {
            *(matrix+i) = malloc(sizeof(int)*m);
            if(*(matrix+i)==NULL)
            {
                for(i--; i>=0; i--)
                {
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
    printf_s("\nBefore: \n");
    valuesOutput(n, m, &*matrix);
    matrixTransposition(n, m, &*matrix);
    printf_s("\nAfter: \n");
    valuesOutput(n, m, &*matrix);
}

void matrixInput(int* n, int* m)
{
    printf_s("\nn: ");
    scanf_s("%i", &*n);
    printf_s("\nm: ");
    scanf_s("%i", &*m);

}

int** malloc_matrix(int n, int m, int** matrix)
{
    matrix = malloc(sizeof(int*)*n);
    if(matrix!=NULL)
    {
        for(int i=0; i<n; i++)
        {
            *(matrix+i) = malloc(sizeof(int)*m);
            if(*(matrix+i)==NULL)
            {
                for(i--; i>=0; i--)
                {
                    free(matrix+i);
                }
                free(matrix);
                *matrix=NULL;
                break;
            }
        }
    }
}

void valuesInput(int n, int m, int** matrix)
{
    printf_s("Input array elements: \n");
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            printf_s("\na[%i%s%i%s", i, "][", j, "]: ");
            scanf_s("%i", &*(*(matrix+i)+j));
        }
    }
}

void valuesOutput(int n, int m, int** matrix)
{
    for(int i=0; i<m; i++) {
        printf_s("%8.1i", i);
    }
    for(int i=0; i<n; i++) {
        printf_s("\n%i", i);
        for(int j=0; j<m; j++) {
            printf_s("  %5.i%s", *(*(matrix+i)+j), " ");
        }
    }
}

void matrixTransposition(int n, int m, int** matrix)
{
    int middleLine = (n-1) / 2;
    for(int i=0; i<(n-1); i++) {
        for(int j=0; (i+j)<(n-1); j++) {
            int bufferValue = *(*(matrix+i)+j);
            *(*(matrix+i)+j) = *(*(matrix+n-1-j)+m-1-i);
            *(*(matrix+n-1-j)+m-1-i) = bufferValue;
        }
    }
}