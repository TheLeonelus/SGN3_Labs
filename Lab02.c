#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInappropriate input.\n"

void borderValuesInput(int *a, int *b);
void xValuesOutput(int a, int b, int *ii);
double expressionFunction(int x);

int main()
{
    double functionResult;
    int a,b,i;
    borderValuesInput(&a, &b);
    printf_s("\nfor:");
    xValuesOutput(a,b, &i);
    for(i; i<=b; ++i) {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
    }
    printf_s("\n\nwhile:");
    xValuesOutput(a,b, &i);
    i = a;
    while (i<=b) {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    }
    printf_s("\n\ndo while:");
    xValuesOutput(a,b, &i);
    do {
        if(i==0)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    } while (i<=b);
    return EXIT_SUCCESS;
}

double expressionFunction(int x)
{
    double result = sqrt(x);
    return result;
}

void xValuesOutput(int a, int b, int*ii)
{
    printf_s("\n  x  ");
    int i;
    for(i=a; i<=b; i++) {
        printf(" | %3.1d%s", i, "  ");
    }
    printf_s("\n f(x)");
    *ii = a;
}

void borderValuesInput(int *a, int *b)
{
    int k;
    do {
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