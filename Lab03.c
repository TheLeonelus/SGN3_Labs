#include <stdlib.h>
#include <stdio.h>
#include <math.h>   

void integralBordersInput();
void precisionInput();
void stepSize(int splitAmount, double *a, double *b);
double xCalculation(int i, double *a);
double fxCalculation(double x);
double integralCalculation(int splitAmount, double a);

double H, E;
int k;

int main()
{
    double a, b;
    integralBordersInput(&a, &b);
    precisionInput();
    int splitAmount = 2; // Количество участков разбиения
    stepSize(splitAmount, &a, &b);
    k=0;
    double pastAreaValue, currentAreaValue;
    pastAreaValue = currentAreaValue = integralCalculation(splitAmount, a);
    printf_s("");
    while(k<1)
    {
        pastAreaValue = currentAreaValue;
        splitAmount = 2*splitAmount; // Увеличение точности подсчётом
        stepSize(splitAmount, &a, &b);
        currentAreaValue = integralCalculation(splitAmount, a);
        printf_s("");
        if(E>(pastAreaValue-currentAreaValue))
        {
            k++;
        }
    }
    printf("\nResult: %lf", currentAreaValue);
    return EXIT_SUCCESS;
}

void integralBordersInput(double *a, double *b)
{
    int k=0;
    while(k<1)
    {
        printf_s("\nInput left border of the segment: ");
        scanf_s("%lf", &*a);
        printf_s("\nInput right border of the segment: ");
        scanf_s("%lf", &*b);
    if (*a>*b)
        printf_s("%s", "Inappropriate input.");
    else ++k;
    }
}

void precisionInput()
{
    printf_s("\nInput precision of calculations: ");
    scanf_s("%lf", &E);
}

void stepSize(int splitAmount, double *a, double *b)
{
    H = (*b-*a)/(2*splitAmount); // Приращение функции
}

double xCalculation(int n, double *a)
{
    double result = *a+n*H; 
    return result;
}

double fxCalculation(double x)
{
    double result = log(x);
    return result;
}

double integralCalculation(int splitAmount, double a)
{
    double array[2][(2*splitAmount)+1], firstSum, secondSum;
    firstSum = secondSum = 0;
    for(int i=0;i<=((2*splitAmount)+1);i++) // Заполнение xi и f(xi)
    {
        array[0][i] = xCalculation(i, &a);
        array[1][i] = fxCalculation(array[0][i]);
    }
    for(int i=1;i<=(splitAmount);i++) // Вычисление суммы нечётных f(x)
    {
        firstSum = firstSum + array[1][2*i-1];
    }
    for(int i=1;i<=(splitAmount-1);i++) // Вычисление суммы чётных f(x)
    {
        secondSum = secondSum + array[1][2*i];
    }
    double result = (H/3)*(array[1][0]+4*firstSum+2*secondSum+array[1][2*splitAmount+1]); // Формула Симпсона
    return result;
}
