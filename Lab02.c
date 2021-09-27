#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInapprorpiate input.\n"

double xValuesInput();
double xValuesOutput();
double yValuesOutput();
double expressionFunction(double x);
double yArrayZeroing();
int zeroCheck();

double array[3][3]; // Возможно ли сделать динамическим?
int k=1;
int cycleType=1;

double main(void)
{
    xValuesInput();
    zeroCheck();
    xValuesOutput();
    for(k=0;k<=3;++k)
    {
        array[k][1] = expressionFunction(array[k][0]);
    }
    yValuesOutput();
    yArrayZeroing();
    xValuesOutput();
    while(k<=3)
    {
        array[k][1] = expressionFunction(array[k][0]);
        ++k;
    }
    yValuesOutput();
    yArrayZeroing();
    xValuesOutput();
    do
    {
        array[k][1] = expressionFunction(array[k][0]);
        k++;
    }
    while(k<=3);
    yValuesOutput();
}

double xValuesInput()
{
    double a;
    double b;
    do
    {
    printf_s("\nInput left border of values: ");
    scanf_s("%lf", &a);
    printf_s("\nInput right border of values: ");
    scanf_s("%lf", &b);
    if (a>b)
        printf_s("%s", INAPPROPRIATEINPUT);
    else ++k;
    }
    while(k<2);
    k=1;
    printf_s("\nInput value of x c [%3.3lf%s%3.3lf%s", a, ";", b, "]");
    do
    {
        
        printf_s("\nx%d%s", k, ": ");
        scanf_s("%lf", &array[k-1][0]);
        if((array[k-1][0]>b)||(array[k-1][0]<a))
            printf_s("%s", INAPPROPRIATEINPUT);
        else ++k;
    }
    while (k<=3);
}

double xValuesOutput()
{
    switch(cycleType)
    {
        case 1:
        {
            printf("\nfor: ");
            break;
        }
        case 2:
        {
            printf("\nwhile: ");
            break;
        }
        case 3:
        {
            printf("\ndo while: ");
            break;
        }
    }
    printf_s("\n   x  | %3.3lf%s%3.3lf%s%3.3lf%s", array[0][0], " | ", array[1][0], " | ", array[2][0], " |");
}

double yValuesOutput()
{
    printf_s("\n f(x) | ");
    for(int i=0;i<=2;i++)
    {
        if(array[i][2]==1)
            printf_s(" NaN  | ");
        else
            printf_s("%3.3lf%s", array[i][1], " | ");
    }
    printf_s("\n");
}

double expressionFunction(double x)
{
    double result = (sin(x)*sin(x))/x;
    return result;
}

double yArrayZeroing()
{
    for(k=0;k<=3;++k)
    {
        array[k][1] = 0;
    }
    k=0;
    cycleType++;
}

int zeroCheck()
{
    int zero = 0;
    for(int i=0;i<=2;i++)
    {
        if(abs(array[i][0])<0.000001)
        {
             array[i][2]=1;
        }
            printf_s("\nCheck: %lf", array[i][0]);
            printf_s("\nCheck: %lf", array[i][2]);
        }
    
}

// Цикл из 3 итераций
// Ввод x1-x4
// Подсчёт с помощью for
// Подсчёт с помощью while
// Подсчёт с помощью do-while
// Отдельно:
// Функция ввода (1<=x<=4)
// Функция подсчёта f(x)=g(x)
// Функция вывода значений x_n
// Функция вывода значений f(x_n)
