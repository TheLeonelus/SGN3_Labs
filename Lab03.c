#include <stdlib.h>
#include <stdio.h>
#include <math.h>   

void integralBordersInput();
void precisionInput();
void stepSize();
double xCalculation(int i);
double fxCalculation(double x);
double integralCalculation();

double a, b, H, E;
int splitAmount, k;

int main()
{
    integralBordersInput();
    precisionInput();
    splitAmount = 2; // Количество участков разбиения
    stepSize();
    k=0;
    double pastAreaValue, currentAreaValue;
    pastAreaValue = currentAreaValue = integralCalculation();
    printf_s("");
    while(k<1)
    {
        pastAreaValue = currentAreaValue;
        splitAmount = 2*splitAmount; // Увеличение точности подсчётом
        stepSize();
        currentAreaValue = integralCalculation();
        printf_s("");
        if(E>(pastAreaValue-currentAreaValue))
        {
            k++;
        }
    }
    printf("\nResult: %lf", currentAreaValue);
    return EXIT_SUCCESS;
}

void integralBordersInput()
{
    int k=0;
    while(k<1)
    {
        printf_s("\nInput left border of the segment: ");
        scanf_s("%lf", &a);
        printf_s("\nInput right border of the segment: ");
        scanf_s("%lf", &b);
    if (a>b)
        printf_s("%s", "Inappropriate input.");
    else ++k;
    }
}

void precisionInput()
{
    printf_s("\nInput precision of calculations: ");
    scanf_s("%lf", &E);
}

void stepSize()
{
    H = (b-a)/(2*splitAmount); // Приращение функции
}

double xCalculation(int n)
{
    double result = a+n*H; 
    return result;
}

double fxCalculation(double x)
{
    double result = log(x);
    return result;
}

double integralCalculation()
{
    double array[2][(2*splitAmount)+1], firstSum, secondSum;
    firstSum = secondSum = 0;
    for(int i=0;i<=((2*splitAmount)+1);i++) // Заполнение xi и f(xi)
    {
        array[0][i] = xCalculation(i);
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
