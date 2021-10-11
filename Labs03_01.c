#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void precisionInput();
double factorialCalculation();

int main()
{
    double E;
    precisionInput(&E);
    int k = 0, i = 0;
    double factorialN = 1, currentSum, pastSum;
    while (k<1) {
        i++;
        factorialN *= factorialCalculation(i);
        currentSum += factorialN;
        if((currentSum-pastSum)<E)
            k++;
        else
            pastSum = currentSum;
    }
    printf_s("Inverse factorial sum: %lf", currentSum);
    printf_s("\nDecimal approximation for comparision: 1.718281828459");
    return EXIT_SUCCESS;
}

void precisionInput(double *E)
{
    printf_s("\nInput precision of calculations: ");
    scanf_s("%lf", &*E);
}

double factorialCalculation(int n)
{
    double result = 1.0 / n;
    return result;
}

