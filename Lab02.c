#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInappropriate input.\n"

void borderValuesInput(double *a, double *b);
void xValuesOutput();
double expressionFunction(int x);

int main()
{
    double functionResult;
    int a,b;
    borderValuesInput(&a, &b);
    printf_s("\nfor:");
    xValuesOutput(a,b);
    int i;
    for(i=a; i<=b; ++i) {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
    }
    printf_s("\n\nwhile:");
    xValuesOutput(a,b);
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
    xValuesOutput(a,b);
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

void xValuesOutput(double a, double b)
{
    printf_s("\n  x  ");
    int i;
    for(i=a; i<=b; i++) {
        printf(" | %3.d%s", i, "  ");
    }
    printf_s("\n f(x)");
}

void borderValuesInput(double *a, double *b)
{
    int k;
    do
    {
    printf_s("\nInput left border of values: ");
    scanf_s("%d", &*a);
    printf_s("\nInput right border of values: ");
    scanf_s("%d", &*b);
    if (*a>*b)
        printf_s("%s", INAPPROPRIATEINPUT);
    else k++;
    }
    while(k<1);
}