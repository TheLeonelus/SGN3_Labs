#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INAPPROPRIATEINPUT "\nInappropriate input.\n"

void borderValuesInput(int *a, int *b);
void xValuesOutput(int a, int b);
double expressionFunction(int x);
int exceptionCheck(int i);
void forCycle(int b, int i);
void whileCycle(int b, int i);
void doWhileCycle(int b, int i);

int main()
{
    double functionResult;
    int a,b;
    borderValuesInput(&a, &b);
    printf_s("\nfor:");
    xValuesOutput(a, b);
    forCycle(b, a);
    printf_s("\n\nwhile:");
    xValuesOutput(a, b);
    whileCycle(b, a);
    xValuesOutput(a, b);
    doWhileCycle(b, a);
    return EXIT_SUCCESS;
}

double expressionFunction(int x)
{
    double result = sqrt(x);
    return result;
}

void xValuesOutput(int a, int b)
{
    printf_s("\n  x  ");
    int i;
    for(i=a; i<=b; i++) {
        printf(" | %3.1d%s", i, "  ");
    }
    printf_s("\n f(x)");
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

int exceptionCheck(int i)
{
    if(i<=0)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

void forCycle(int b, int i)
{
    for(i; i<=b; ++i) {
        if(exceptionCheck==1)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
    }
}

void whileCycle(int b, int i)
{
    while (i<=b) {
        if(exceptionCheck==1)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    }
}

void doWhileCycle(int b, int i)
{
    do {
        if(exceptionCheck==1)
            printf_s(" |  NaN ");
        else
            printf_s(" | %3.3lf", expressionFunction(i));
        i++;
    } while (i<=b);
}