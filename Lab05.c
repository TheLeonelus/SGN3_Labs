#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define NUMBERTYPE 10
#define DIGITSIZE 10

void inputSize(int *size);
int arrayMalloc(int **array, int size);
void arrayFullfill(int *array, int size);
void arrayOutput(int *array, int size);
void radixSortLSD(int *array, int size); // Radix sort | Least Significant DIGITSIZEit version
int countSort(int *array, int size, int exp); // Counting sort
void countPositiveNegative(int *array, int *pCount, int *nCount, int size);
void sideArraySortPos(int *array, int *sideArray, int size, int sideSize);
void sideArraySortNeg(int *array, int *sideArray, int size, int sideSize);
void arrayAssemble(int *array, int *pArray, int *nArray, int pCount, int nCount, int size);


int main(void)
{
    int size = 0, *array, nCount = 0, pCount = 0, *nArray, *pArray;
    inputSize(&size);
    if(arrayMalloc(&array, size)) // Memory allocate for main array
        return EXIT_FAILURE;
    arrayFullfill(array, size); // Fullfilling main array
    printf_s("\nOriginal array:");
    arrayOutput(array, size);
    //LARGE_INTEGER performanceCounter;
    //QueryPerformanceFrequency(&performanceCounter);
    //LARGE_INTEGER performanceCounterStart;
    //QueryPerformanceCounter(&performanceCounterStart);
    countPositiveNegative(array, &pCount, &nCount, size);
    if(arrayMalloc(&pArray, pCount) == 1)
        return EXIT_FAILURE;
    if(arrayMalloc(&nArray, nCount) == 1)
        return EXIT_FAILURE;
    sideArraySortPos(array, pArray, size, pCount);
    sideArraySortNeg(array, nArray, size, nCount);
    arrayAssemble(array, pArray, nArray, pCount, nCount, size);
    //LARGE_INTEGER performanceCounterEnd;
    //QueryPerformanceFrequency(&performanceCounterEnd);
    // Конвертировать LARGE_INTEGER в double*
    //double timeElapsed = (double*)(performanceCounterEnd) - (double*)(performanceCounterEnd);
    //printf_s("Time elapsed: %lf\n", timeElapsed);
    printf_s("\nFinal array:");
    arrayOutput(array, size);
    free(pArray);
    free(nArray);
    free(array);
    
    return EXIT_SUCCESS;
}
void inputSize(int *size)
{
    printf_s("Input array size: ");
    scanf_s("%d", &*size);
}

int arrayMalloc(int **array, int size)
{
    *array = (int*) malloc(size*sizeof(int));
    if (*array == NULL) {
        free(*array);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void arrayFullfill(int *array, int size)
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
        int range;
        printf_s("\nInput range of possible numbers: ");
        scanf_s("%i", &range);
        for (int i = 0; i < size; i++) {
            int element = range - (rand()%(range*2));
            *(array+i) = element;
            if(*(array+i)==range - (rand()%(range*2)))
                *(array+i) = 0;
        }
    }
    else {
        printf_s("\n");
        for (int i = 0; i < size; i++) {
                printf_s("\nArray[%i%s", i, "]: ");
                scanf_s("%i", &*(array+i));
        }
    }
}

int getMaximumValue(int *array, int size)
{
    int MaxElement = *array;
    for (int i=0; i<size; i++) {
        if(*(array+i)>MaxElement) {
            MaxElement = *(array+i);
        }
    }
    return MaxElement;
}

void radixSortLSD(int *array, int size)
{
    int maximumElement = getMaximumValue(array, size);
    for (int exp = 1; maximumElement / exp > 0; exp *= DIGITSIZE) {
        countSort(array, size, exp);
    }
}

int countSort(int *array, int size, int exp)
{
    int *arrayTemp;
    int *count;
    arrayMalloc(&arrayTemp, size);
    arrayMalloc(&count, NUMBERTYPE);
    for (int i = 0; i < NUMBERTYPE; i++)
		*(count + i) = 0;
	for (int i = 0; i < size; i++)
		*(count + ((*(array+i) / exp) % DIGITSIZE)) += 1;
	for (int i = 1; i < NUMBERTYPE; i++)
		*(count+i) += *(count + i - 1);
	for (int i = size - 1; i >= 0; i--) {
		*(arrayTemp + *(count + ((*(array+i) / exp) % DIGITSIZE)) - 1) = *(array+i);
		*(count + ((*(array+i) / exp) % DIGITSIZE)) -= 1;
	}
	for (int i = 0; i < size; i++)
		*(array+i) = *(arrayTemp + i);
    free(arrayTemp);
    free(count);
    return EXIT_SUCCESS;
}

void arrayOutput(int *array, int size)
{
    printf_s("\n");
    for(int i = 0; i < size; i++)
        printf_s(" i%3.1d%s%6.1d%c", i, ": ", *(array+i), i%5-4 ? ' ' : '\n');
    printf_s("\n");
}

void countPositiveNegative(int *array, int *pCount, int *nCount, int size)
{
    for (int i = 0; i < size; i++) {
        if(*(array+i)>0) {
            *pCount += 1;
        }
        else {
            if(*(array+i)<0)
                *nCount += 1;
        }
    }
}

void sideArraySortPos(int *array, int *sideArray, int size, int sideSize)
{
    int element = 0;
    for(int i = 0; i < size; i++) {
        if(*(array+i)>0) {
            *(sideArray+element) = *(array+i);
            element++;
        }
    }
    radixSortLSD(sideArray, sideSize);
}

void sideArraySortNeg(int *array, int *sideArray, int size, int sideSize)
{
    int element = 0;
    for(int i = 0; i < size; i++) {
        if(*(array+i)<0) {

            *(sideArray+element) = abs(*(array+i));
            element++;
        }
    }
    radixSortLSD(sideArray, sideSize);
}

void arrayAssemble(int *array, int *pArray, int *nArray, int pCount, int nCount, int size)
{
    for (int i = 0; i < pCount; i++)
        *(array + i) = *(pArray + i);
    for (int i = pCount; i < pCount + nCount; i++)
        *(array + i) = (-1) * *(nArray + i - pCount);
    for (int i = pCount + nCount; i < size; i++)
        *(array + i) = 0;
}
// Пользователь вводит размер массива и значения его элементов с клавиатуры. Память под массив выделяется динамически.
// Необходимо сгруппировать и отсортировать массив следующим образом:
// 0 вар. положительные по возрастанию, отрицательные по убыванию, нули     