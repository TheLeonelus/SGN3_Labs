#include <stdio.h>

#define RIGHTPRINT printf("\nPoint is to the right side from vector (p1,p1).")
#define LEFTPRINT printf("\nPoint is to the left side from vector (p1,p2).")
#define INCLUDEPRINT printf("\nLine includes the point.")
#define INAPPROPRIATEINPUT printf("Inappropriate input!")

int pointInput(int number, int casetype); // casetype - Происходит ввод X(1) или Y(2)
int isIncludeCheck(int x1, int x2, int x3, int y1, int y2, int y3);
int isSectorCheck(int x1, int x2, int x3, int y1, int y2, int y3);
int sectorPrint(int n);

int main(void)
{
    printf("Input number of points (assuming that points 1(Top),2(Right) <and 3(Left)> are apexes of the lines [3/4]: ");
    int n;
    scanf("%d", &n);
    switch(n) {
        case 3: { // Line-case
            int array[3][2];
            for (int k=1; k<=3; ++k) {
                array[k-1][0]=pointInput((k),1);
                array[k-1][1]=pointInput((k),2);
            }  
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 0: {
                    if((array[0][0]==array[1][0])) {
                        if(array[0][1]>array[1][1]) {
                            if(array[0][0]<array[2][0])
                                return LEFTPRINT;
                            return RIGHTPRINT;
                        }
                        if(array[0][0]<array[2][0])
                            return RIGHTPRINT;
                        return LEFTPRINT;
                    }
                    int y13 = ((array[2][0]-array[1][0])*(array[0][1]-array[1][1]))/(array[0][0]-array[1][0])+array[1][1];
                    if((array[1][0]-array[0][0])>0) {
                        if(array[2][1]<y13)
                            return RIGHTPRINT;
                        return LEFTPRINT;
                    }
                    if(array[2][1]<y13)
                        return LEFTPRINT;
                    return RIGHTPRINT;
                    }
                }
                case 1: {
                    return INAPPROPRIATEINPUT;
                }
                case 2: {
                    return INCLUDEPRINT;
                }
            }
        case 4: { // triangle-case
            int array[4][2];
            for (int k=1; k<=4; ++k) {
                array[k-1][0]=pointInput(k, 1);
                array[k-1][1]=pointInput(k, 2);
            }
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 1: {
                    return INAPPROPRIATEINPUT;
                }
                case 2: {
                    return INAPPROPRIATEINPUT;
                }
                case 0: {
                    if((isIncludeCheck(array[0][0], array[1][0], array[3][0], array[0][1], array[1][1], array[3][1])==0)&&(isIncludeCheck(array[1][0], array[2][0], array[3][0], array[1][1], array[2][1], array[3][1])==0)&&(isIncludeCheck(array[0][0], array[2][0], array[3][0], array[0][1], array[2][1], array[3][1])==0)) {
                        if(isSectorCheck(array[0][0], array[2][0], array [3][0], array[0][1], array[2][1], array[3][1])==1) {
                            if(isSectorCheck(array[0][0], array[1][0], array [3][0], array[0][1], array[1][1], array[3][1])==1)
                                return sectorPrint(1);
                            if(isSectorCheck(array[1][0], array[2][0], array [3][0], array[1][1], array[2][1], array[3][1])==1)
                                return sectorPrint(6);
                            return sectorPrint(5);
                        }
                        if(isSectorCheck(array[0][0], array[1][0], array [3][0], array[0][1], array[1][1], array[3][1])==1) {
                            if(isSectorCheck(array[1][0], array[2][0], array[3][0], array[1][1], array[2][1], array[3][1])==1)
                                return sectorPrint(2);
                            return sectorPrint(3);
                        }
                        if(isSectorCheck(array[1][0], array[2][0], array [3][0], array[1][1], array[2][1], array[3][1])==1)
                            return sectorPrint(7);
                        return sectorPrint(4);
                    }
                    return INCLUDEPRINT;
                }
            }          
        }
    }
}

int pointInput(int number, int casetype)
{
    int coord; 
    switch(casetype)
    {
        case(1):
        {
            printf("\nInput point %i%s%i%s",number, ":\nx", number, ": ");
            scanf("%d", &coord);
            return coord;
        }
        case(2):
        {
            printf("\ny%i%s", number, ": ");
            scanf("%d", &coord);
            return coord;
        }
    }
}

int isIncludeCheck(int x1, int x2, int x3, int y1, int y2, int y3)
{
    if((x1==x2)&&(y1==y2))
        return 1; // Неверный ввод
    if(((x1==x2)&&(x2==x3))||((y1==y2)&&(y2==y3)))
        return 2; // 3 точки лежат на одной прямой
    if(x1==x2)
    {
        if(x2==x3)
            return 2;
    }   
        else 
    {
        if (y3==(((x3-x2)*(y1-y2))/(x1-x2)+y2)) 
            return 2;
    }
    if (x3==x2)
    {
        if(y2==y3)
            return 2;
    }
    return 0;
}

int isSectorCheck(int x1, int x2, int x3, int y1, int y2, int y3)
{
    if((x1==x2)||(x2==x3)||(y1==y2))
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


int sectorPrint(int n) // Вывод номера сектора
{
    printf("\nPoint is in the №%i%s", n, " sector.");
}
// Сектора:
// 1 - Угловой точки p1
// 2 - Боковой прямой p1-p2
// 3 - Угловой прямой p2
// 4 - Боковой прямой p2-p3
// 5 - Угловой точки p3
// 6 - Боковой прямой p1-p3
// 7 - Внутренний