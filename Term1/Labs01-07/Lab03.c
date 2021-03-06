#include <stdlib.h>
#include <stdio.h>
#include <math.h>   

void integralBordersInput(double *a, double *b);
void precisionInput(double *E);
void stepSize(int splitAmount, double a, double b, double *H);
double xCalculation(int i, double a, double H);
double fxCalculation(double x);
double integralCalculation(int splitAmount, double a, double H);

int main()
{
    double a, b;
    integralBordersInput(&a, &b);
    double E;
    precisionInput(&E);
    int splitAmount = 2; // Количество участков разбиения
    double H;
    stepSize(splitAmount, a, b, &H);
    double pastAreaValue, currentAreaValue;
    pastAreaValue = currentAreaValue = integralCalculation(splitAmount, a, H);
    int k=0;
    while(k<1) {
        pastAreaValue = currentAreaValue;
        splitAmount = 2*splitAmount; // Увеличение точности подсчётов
        stepSize(splitAmount, a, b, &H);
        currentAreaValue = integralCalculation(splitAmount, a, H);
        if(E>(pastAreaValue-currentAreaValue)) {
            k++;
        }
    }
    printf("\nResult: %lf", currentAreaValue);
    return EXIT_SUCCESS;
}

void integralBordersInput(double *a, double *b)
{
    int k=0;
    while(k<1) {
        printf_s("\nInput left border of the segment: ");
        scanf_s("%lf", &*a);
        printf_s("\nInput right border of the segment: ");
        scanf_s("%lf", &*b);
    if (*a>*b)
        printf_s("%s", "Inappropriate input.");
    else k++;
    }
}

void precisionInput(double *E)
{
    printf_s("\nInput precision of calculations: ");
    scanf_s("%lf", &*E);
}

void stepSize(int splitAmount, double a, double b, double *H)
{
    *H = (b-a)/(2*splitAmount); // Приращение функции
}

double xCalculation(int n, double a, double H)
{
    double result = a+n*H; 
    return result;
}

double fxCalculation(double x)
{
    double result = log(x);
    return result;
}

double integralCalculation(int splitAmount, double a, double H)
{
    double firstSum, secondSum;
    double* arrayX;
    double* arrayFx;
    arrayX = malloc((2*splitAmount+1)*sizeof(double));
    arrayFx = malloc((2*splitAmount+1)*sizeof(double));
    firstSum = secondSum = 0;
    for(int i=0; i<=((2*splitAmount)+1); i++) { // Заполнение x(i) и f(x(i))
        *(arrayX+i) = xCalculation(i, a, H);
        *(arrayFx+i) = fxCalculation(*(arrayX+i));
    }
    for(int i=1; i<=splitAmount; i++) { // Вычисление суммы нечётных f(x)
        firstSum += *(arrayFx+2*i-1);
    }
    for(int i=1; i<=(splitAmount-1); i++) { // Вычисление суммы чётных f(x)
        secondSum += *(arrayFx+2*i);
    }
    double result = (H/3)*(*arrayFx+4*firstSum+2*secondSum+*(arrayFx+2*splitAmount+1)); // Формула Симпсона
    free(arrayX);
    free(arrayFx);
    return result;
}