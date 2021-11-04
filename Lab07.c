#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define NUMBERTYPE 10
#define DIGITMOVE 10

void matrixInput(int *n);
void malloc_matrix(int n, int ***matrix);
void valuesInput(int n, int **matrix);
void valuesOutput(int n, int **matrix);
int getMaximumValue(int *array, int n);
int arrayMalloc(int **array, int n);
void radixSortLSD(int *array, int n);
int countSort(int *array, int n, int exp);
void matrixAssembly(int *array, int **matrix, int n);

int main(void)
{
    int n, **matrix, *bufferArray;
    matrixInput(&n);
    malloc_matrix(n, &matrix);
    arrayMalloc(&bufferArray, n*n);
    valuesInput(n, matrix);
    printf_s("\n\nOriginal: \n");
    valuesOutput(n, matrix);
    printf_s("\n");
    for(int i = 0, k = 0; i < n; i++) {
        for(int j = 0; j < n; j++, k++) {
            *(bufferArray + n*n - 1 - k) = *(*(matrix + i) + j);
        }
    }
    radixSortLSD(bufferArray, n);
    matrixAssembly(bufferArray, matrix, n);
    printf_s("\n\nFinal: \n");
    valuesOutput(n, matrix);
    free(bufferArray);
    return EXIT_SUCCESS;
}

void matrixInput(int *n) 
{
    int k = 0;
    while (k < 1) {
        printf_s("\nInput amount of lines: ");
        scanf_s("%i", &*n);
        if ((*n <= 0)||((*n % 2) == 0 ))
            printf_s("\nInappropriate Input! Please try again.");
        else
            break;
    }
}

void malloc_matrix(int n, int ***matrix)
{
    *matrix = (int**) malloc(sizeof(int *) * n);
    if (*matrix != NULL) {
        for (int i = 0; i < n; i++) {
            *(*matrix + i) = (int*) malloc(sizeof(int) * n);
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

void valuesInput(int n, int **matrix)
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
        int element = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                *(*(matrix + i) + j) = element;
                element++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf_s("\nArray[%i%s%i%s", i, "][", j, "]: ");
                scanf_s("%i", &*(*(matrix + i) + j));
            }
        }
    }
}

void valuesOutput(int n, int **matrix)
{
    printf_s("n | m ");
    for (int i = 0; i < n; i++) {
        printf_s(" %1.1i%s", i, "     ");
    }
    printf_s("\n  |");
    for (int i = 0; i < n; i++) {
        printf_s("-------");
    }
    for (int i = 0; i < n; i++) {
        printf_s("\n  |\n%i%s", i, " |");
        for (int j = 0; j < n; j++) {
            printf_s("  %4.1i%s", *(*(matrix + i) + j), " ");
        }
    }
}

int arrayMalloc(int **array, int n)
{
    *array = (int*) malloc(n*sizeof(int));
    if (*array == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int getMaximumValue(int *array, int n)
{
    int maxValue = *array;
    for (int i = 0; i < n*n; i++) {
            if(*(array+i) > maxValue) 
                maxValue = *(array+i);
    }
    return maxValue;
}

void radixSortLSD(int *array, int n)
{
    int maximumElement = getMaximumValue(array, n);
    for (int exp = 1; maximumElement / exp > 0; exp *= DIGITMOVE) {
        countSort(array, n, exp);
    }
}

int countSort(int *array, int n, int exp)
{
    int *tempArray, *count;
    int size = n*n;
    arrayMalloc(&tempArray, size);
    count = (int*) calloc(NUMBERTYPE, sizeof(int));
	for (int i = 0; i < n*n; i++)
            *(count + ((*(array+i) / exp) % DIGITMOVE)) += 1;
	for (int i = 1; i < NUMBERTYPE; i++) {
		*(count+i) += *(count + i - 1);
    }
	for (int i = n*n - 1; i >= 0; i--) {
		*(tempArray + *(count + ((*(array+i) / exp) % DIGITMOVE)) - 1) = *(array+i);
		*(count + ((*(array+i) / exp) % DIGITMOVE)) -= 1;
	}
    printf_s("\n");
    for(int i = 0; i < n*n; i++)
        *(array + i) = *(tempArray + i);
    free(tempArray);
    free(count);
    return EXIT_SUCCESS;
}

void matrixAssembly(int *array, int **matrix, int n)
{
    int center = (n - 1) / 2;
    int check = 0;
    int min = center - 1, max = center + 1, mI = center , mJ = center, i = 0;
    for (; max <= (n - 1); min--, max++) {
        if(check) {
            mI--;
            mJ++;
        }
        for (; mI >= min; mI--, i++)
            *(*(matrix + mI) + mJ) = *(array + i);
        for (mI++, mJ++; mJ <= max; mJ++, i++)
            *(*(matrix + mI) + mJ) = *(array + i);
        for (mI++, mJ--; mI <= max; mI++, i++)
            *(*(matrix + mI) + mJ) = *(array + i);
        if(!check)
            check++;
        for (mI--, mJ--; mJ >= min; mJ--, i++)
            *(*(matrix + mI) + mJ) = *(array + i);
    }
    i--;
    mJ++;
    for(; mI >= 0; mI--, i++) {
        *(*(matrix + mI) + mJ) = *(array + i);
    }
}

// Вводится матрица. Отсортировать матрицу змейкой
// вар. (вариант на доп. баллы) змейка от центра по спирали
