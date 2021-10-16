#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 0.00000001

int inputSize(int *size);
int getLastZeroElement(double *array, int size);
int getMaxValueElement(double *array, int size, int zeroElement);
double averageSummary(int leftBorderSummary, int rightBorderSummary, double *array);

int main(void)
{
    int size;
    double* array;
    inputSize(&size);
    array = malloc(size*sizeof(double));
        printf_s("\nInput array elements: ");
    for(int i=0; i<size; i++) {
        printf_s("\ni%d%s", i, ": ");
        scanf_s("%lf", &*(array+i));
        printf_s("checK:%lf \n", *(array+i));
    }
    printf_s("\nAverage summary of elements: %.3lf", averageSummary(getLastZeroElement(array, size), getMaxValueElement(array, size, getLastZeroElement(array, size)), array));
    free(array);
    return EXIT_SUCCESS;
}

int inputSize(int *size)
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

int getLastZeroElement(double *array, int size)
{
    int zeroElement;
    for (int i=0; i<size; i++) {
        if(fabs(*(array+i))<PRECISION)
            zeroElement = i;
    }
    printf_s("\n%i\n", zeroElement);
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
    printf_s("\n%i\n", MaxIndex);
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