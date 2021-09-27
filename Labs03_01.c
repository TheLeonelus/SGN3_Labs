#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void precisionInput();

double E;

int main()
{
    precisionInput();

    return EXIT_SUCCESS;
}

void precisionInput()
{
    printf_s("\nInput precision of calculations: ");
    scanf_s("%lf", &E);
}

double factorialCalculation(int n)
{
    
    double result = 1 / n;
}
