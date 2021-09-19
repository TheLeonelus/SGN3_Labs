#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInapprorpiate input."

double xValuesOutput(int n);

double yValuesOutput();

double expressionFunction(double x);

double yArrayZeroing();

double array[2][3]; // array containing X

int k=1;

double main(void)
{
    char s[3];
    printf_s("\nInput value of x c [1;4]");
    do
    {
        
        printf_s("\nx%d%s", k, ": ");
        scanf_s("%lf", &array[k-1][0], (unsigned)_countof(s));
        // printf_s("\n%.3lf", array[k]);
        if((array[k-1][0]>4.0)||(array[k-1][0]<1.0)) printf("%s", INAPPROPRIATEINPUT);
        else ++k;
    }
    while (k<=3);
    xValuesOutput(1);
    for(k=0;k<=3;++k)
    {
        array[k][1] = expressionFunction(array[k][0]);
    }
    yValuesOutput();
    yArrayZeroing();
    xValuesOutput(2);
    while(k<=3)
    {
        array[k][1] = expressionFunction(array[k][0]);
        ++k;
    }
    yValuesOutput();
    yArrayZeroing();
    xValuesOutput(3);
    do
    {
        array[k][1] = expressionFunction(array[k][0]);
        k++;
    }
    while(k<=3);
    yValuesOutput();
}

double xValuesOutput(int n)
{
    switch(n)
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
    printf_s("\n x | %3.3lf%s%3.3lf%s%3.3lf%s", array[0][0], " | ", array[1][0], " | ", array[2][0], " |");
}

double yValuesOutput()
{
    printf_s("\n y | %3.3lf%s%3.3lf%s%3.3lf%s", array[0][1], " | ", array[1][1], " | ", array[2][1], " |\n");
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
