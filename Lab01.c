#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RIGHTPRINT printf_s("\nPoint is to the right side from vector (p1,p1).")
#define LEFTPRINT printf_s("\nPoint is to the left side from vector (p1,p2).")
#define INCLUDEPRINT printf_s("\nLine includes the point.")
#define INAPPROPRIATEINPUT printf_s("Inappropriate input!")
#define PRECISION 0.00000000001

double pointInput(int number, int casetype); // casetype - Происходит ввод X или Y

int isIncludeCheck(double x1, double x2, double x3, double y1, double y2, double y3);
int isSectorCheck(double x1, double x2, double x3, double y1, double y2, double y3);
int sectorPrint(int n);
int lineCaseCalculation(double x1, double x2, double x3, double y1, double y2, double y3);
int triangleCaseCalculation(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);

int main(void)
{
    printf_s("Input number of points (assuming that points 1(Top),2(Right) <and 3(Left)> are apexes of the lines [3/4]: ");
    int n;
    scanf_s("%d", &n);
    switch(n) {
        case 3: { // Line-case
            double array[3][2];
            for (int k=1; k<=3; ++k) {
                array[k-1][0]=pointInput((k),1);
                array[k-1][1]=pointInput((k),2);
            }  
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 0: {
                    switch(lineCaseCalculation(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                        case 0: {
                            return LEFTPRINT;
                        }
                        case 1: {
                            return RIGHTPRINT;
                        }
                    }
                }
                case 1: {
                    return INAPPROPRIATEINPUT;
                }
                case 2: {
                    return INCLUDEPRINT;
                }
            }
        }
        case 4: { // triangle-case
            double array[4][2];
            for (int k=1; k<=4; ++k) {
                array[k-1][0]=pointInput(k, 1);
                array[k-1][1]=pointInput(k, 2);
            }
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 0: {
                    if((isIncludeCheck(array[0][0], array[1][0], array[3][0], array[0][1], array[1][1], array[3][1])==0)&&(isIncludeCheck(array[1][0], array[2][0], array[3][0], array[1][1], array[2][1], array[3][1])==0)&&(isIncludeCheck(array[0][0], array[2][0], array[3][0], array[0][1], array[2][1], array[3][1])==0)) {
                    return sectorPrint(triangleCaseCalculation(array[0][0], array[1][0], array[2][0], array[3][0], array[0][1], array[1][1], array[2][1], array[3][1]));
                    }
                    return INCLUDEPRINT;
                }
                case 1: {
                    return INAPPROPRIATEINPUT;
                }
                case 2: {
                    return INAPPROPRIATEINPUT;
                }
            }          
        }
    }
}

double pointInput(int number, int casetype)
{
    double coord; 
    int s = 5;
    switch(casetype)
    {
        case(1):
        {
            printf_s("\nInput point %i%s%i%s",number, ":\nx", number, ": ");
            scanf_s("%lf", &coord);
            return coord;
        }
        case(2):
        {
            printf_s("y%i%s", number, ": ");
            scanf_s("%lf", &coord);
            return coord;
        }
    }
}

int isIncludeCheck(double x1, double x2, double x3, double y1, double y2, double y3)
{
    double x12 = fabs(x1-x2);
    double x23 = fabs(x2-x3);
    double y12 = fabs(y1-y2);
    double y23 = fabs(y2-y3);
    if((x12<PRECISION)&&(y12<PRECISION))
        return 1; // Неверный ввод
    if(((x12<PRECISION)&&(x23<PRECISION))||((y12<PRECISION)&&(y23<PRECISION))) {
        return 2; // 3 точки лежат на одной прямой
    }
    if(x12<PRECISION)
    {
        if(x23<PRECISION) {
            return 2;
        }
    }   
        else 
    {
        double count = fabs(y3-(((x3-x2)*(y1-y2))/(x1-x2)+y2));
        if(count<PRECISION) {
            return 2;
        }
    }
    if(x23<PRECISION)
    {
        if(y23<PRECISION) {
            return 2;
        }
    }
    return 0;
}

int isSectorCheck(double x1, double x2, double x3, double y1, double y2, double y3)
{
    double x12 = fabs(x1-x2);
    double x23 = fabs(x2-x3);
    double y12 = fabs(y1-y2);
    if(x12<PRECISION) {
        if(x3>x2)
            return 1; // more
        return 0; // less
    }
    if((x12<PRECISION)||(x23<PRECISION)||(y12<PRECISION))
    {
        if(y3>y2)
            return 1;
        return 0;
    }
    else 
    {
        if(y3>((x3-x2)*(y1-y2)/(x1-x2)+y2)) 
            return 1;
        return 0;
    }
}

int lineCaseCalculation(double x1, double x2, double x3, double y1, double y2, double y3)
{
    double x12=fabs(x1-x2);
    if((x12<PRECISION)) {
        if(y1>y2) {
            if(x1<x3)
                return 0; // left
            return 1; // right
        }
    if(x1<x3)
        return 1;
    return 0;
    }
    double y13 = ((x3-x2)*(y1-y2))/(x1-x2)+y2;
    if((x2-x1)>0) {
        if(y3<y13)
            return 1;
        return 0;
    }
    if(y3<y13)
         return 0;
    return 1;
}

int triangleCaseCalculation(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4)
{
    if(isSectorCheck(x1, x3, x4, y1, y3, y4)==1) {
        if(isSectorCheck(x1, x2, x4, y1, y2, y4)==1)
            return 1;
        if(isSectorCheck(x2, x3, x4, y2, y3, y4)==1)
            return 6;
        return 5;
    }
    if(isSectorCheck(x1, x2, x4, y1, y2, y4)==1) {
        if(isSectorCheck(x2, x3, x4, y2, y3, y4)==1)
            return 2;
        return 3;
    }
    if(isSectorCheck(x2, x3, x4, y2, y3, y4)==1)
        return 7;
    return 4;
}

int sectorPrint(int n)
{
    printf_s("\nPoint is in the №%i%s", n, " sector.\n");
}
// Сектора:
// 1 - Угловой точки p1
// 2 - Боковой прямой p1-p2
// 3 - Угловой прямой p2
// 4 - Боковой прямой p2-p3
// 5 - Угловой точки p3
// 6 - Боковой прямой p1-p3
// 7 - Внутренний