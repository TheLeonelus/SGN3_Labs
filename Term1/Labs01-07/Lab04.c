#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 0.00000001

void inputSize(int *size);
void arrayFullfill(int size, double *array);
int getLastZeroElement(double *array, int size);
int getMaxValueElement(double *array, int size, int zeroElement);
double averageSummary(int leftBorderSummary, int rightBorderSummary, double *array);

int main(void)
{
    int size;
    inputSize(&size);
    double* array = (double*) malloc(size*sizeof(double));
    if(array == NULL) {
        free(array);
        return EXIT_FAILURE;
    }
    arrayFullfill(size, array);
    int zeroElement = getLastZeroElement(array, size);
    printf_s("\nAverage summary of elements: %.3lf", averageSummary(zeroElement, getMaxValueElement(array, size, zeroElement), array));
    free(array);
    return EXIT_SUCCESS;
}

void inputSize(int *size)
{
    int k = 0;
    while(k<1) {
    printf_s("Input size of array: ");
    scanf_s("%d", &*size);
    if(*size<=0)
        printf_s("\nInappropriate input! Try again.\n");
    else 
        k++;
    }
}

void arrayFullfill(int size, double *array)
{
    printf_s("\nInput array elements: ");
    for(int i=0; i<size; i++) {
        printf_s("\ni%d%s", i, ": ");
        scanf_s("%lf", &*(array+i));
    }
}

int getLastZeroElement(double *array, int size)
{
    int zeroElement;
    for (int i=0; i<size; i++) {
        if(fabs(*(array+i))<PRECISION)
            zeroElement = i;
    }
    return zeroElement;
}

int getMaxValueElement(double *array, int size, int zeroElement)
{
    double MaxElement = *(array+zeroElement+1);
    int MaxIndex = zeroElement;
    for (int i=zeroElement+2; i<size; i++) {
        if((*(array+i))>MaxElement) {
            MaxElement = *(array+i);
            MaxIndex = i;
        }
    }
    return MaxIndex;
}

double averageSummary(int leftBorderSummary, int rightBorderSummary, double *array)
{
    double averageSummary = 0.0;
    for(int i=leftBorderSummary; i<rightBorderSummary; i++) // добавить "i<=rightBorderSummary", если макс. значение включено
        averageSummary+=(*(array+i));
    if((rightBorderSummary-leftBorderSummary)>1)
        averageSummary = averageSummary / (rightBorderSummary - leftBorderSummary - 1);
    return averageSummary;
}
// Пользователь вводит размер массива и значения его элементов с клавиатуры. Память под массив необходимо выделять динамически.
// 1 вар. Найти среднее всех элементов от последнего 0 до максимального