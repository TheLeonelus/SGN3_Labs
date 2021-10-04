#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInappropriate input.\n"

void borderValuesInput();
void xValuesOutput();
double expressionFunction(int x);

int a,b;

int main()
{
    double functionResult;
    borderValuesInput();
    printf_s("\nfor:");
    xValuesOutput();
    printf_s("\n f(x)");
    int i;
    for(i=a; i<=b; ++i) {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
    }
    printf_s("\n\nwhile:");
    xValuesOutput();
    printf_s("\n f(x)");
    i = a;
    while (i<=b)
    {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    }
    printf_s("\n\ndo while:");
    xValuesOutput();
    printf_s("\n f(x)");
    i = a;
    do
    {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    } while (i<=b);
    
    
}

double expressionFunction(int x)
{
    double result = sqrt(x);
    return result;
}

void xValuesOutput()
{
    printf_s("\n  x  ");
    int i;
    for(i=a; i<=b; i++) {
        printf(" | %3.d%s", i, "  ");
    }
}

void borderValuesInput()
{
    int k;
    do
    {
    printf_s("\nInput left border of values: ");
    scanf_s("%d", &a);
    printf_s("\nInput right border of values: ");
    scanf_s("%d", &b);
    if (a>b)
        printf_s("%s", INAPPROPRIATEINPUT);
    else k++;
    }
    while(k<1);
}