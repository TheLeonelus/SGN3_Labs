#include <stdio.h>

int xPointInput(int number)
{
    int coord;  // Input of X-coord
    printf("\nInput point %i%s%i%s",number, ":\nx", number, ": ");
    scanf("%d", &coord);
    return coord;
}

int yPointInput(int number)
{
    int coord;  // Input of Y-coord
    printf("\ny%i%s", number, ": ");
    scanf("%d", &coord);
    return coord;
}

int rightPrint(void) // Вывод случая "Точка справа от вектора"
{
    printf("\nPoint is to the right side from vector (p1,p2).");
}

int leftPrint(void) // Вывод случая "Точка слева от вектора"
{
    printf("\nPoint is to the left side from vector (p1,p2).");
}

int includePrint(void) // Точка пренадлежит линии
{
    printf("\nLine includes the point.");
}

int inappropriateInputPrint(void) // Точка лежит на прямой(-ых)
{
    printf("Inappropriate input!");
}

int isIncludeCheck(int x1, int x2, int x3, int y1, int y2, int y3)
{
    if((x1==x2)&&(y1==y2))
        return 1; // Неверный ввод
    if(((x1==x2)&&(x2==x3))||(((y1==y2)&&(y2==y3))||(y3==((x3-x2)*(y1-y2))/(x1-x2)+y2)))
        return 2; // 3 точки лежат на одной прямой
    return 0;
}

int sectorPrint(int n) // Вывод номера сектора
{
    printf("\nPoint is in the №%i%s", n, " sector.");
}

int isSectorCheck(int x1, int x2, int x3, int y1, int y2, int y3)
{
    if(y3>((x3-x2)*(y1-y2)/(x1-x2)+y2)) return 1;
    return 0;
}

int main(void)
{
    printf("Input number of points (assuming that points 1(Top),2(Right) <and 3(Left)> are apexes of the lines [3/4]: ");
    int n; // Number of points
    scanf("%d", &n);
    switch(n) {
        case 3: { // Line-case
            int array[3][2]; // Array with point-coordinates
            int k; // Cycle`s iteration | Number of point
            for (k=1; k<=3; ++k) { // fullfilling the array
                array[k][0]=xPointInput(k);
                array[k][1]=yPointInput(k);
                printf("\nx: %d", array[k][0]);
                printf("\ny: %d", array[k][1]);
            }  
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 0: {
                    if((array[0][0]==array[1][0])) {
                        if(array[0][1]>array[1][1]) {
                            if(array[0][0]<array[2][0])
                                return leftPrint();
                            return rightPrint();
                        }
                        if(array[0][0]<array[2][0])
                            return rightPrint();
                        return leftPrint();
                    }
                    int y13 = ((array[2][0]-array[1][0])*(array[0][1]-array[1][1]))/(array[0][0]-array[1][0])+array[1][1];
                    if((array[1][0]-array[0][0])>0) {
                        if(array[2][1]<y13)
                            return rightPrint();
                        return leftPrint();
                    }
                    if(array[2][1]<y13)
                        return leftPrint();
                    return rightPrint();
                    }
                }
                case 1: {
                    return inappropriateInputPrint();
                }
                case 2: {
                    return includePrint();
                }
            }
        case 4: { // triangle-case
            int array[4][2]; // Array with point-coordinates
            int k; // Cycle`s iteration | Number of point
            for (k=1; k<=4; ++k) { // fullfilling the array
                array[k][0]=xPointInput(k);
                array[k][1]=yPointInput(k);
            }
            switch(isIncludeCheck(array[0][0], array[1][0], array[2][0], array[0][1], array[1][1], array[2][1])) {
                case 1: {
                    return inappropriateInputPrint();
                }
                case 2: {
                    return inappropriateInputPrint();
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
                    return includePrint();
                }
            }          
        }
    }
}



// Сектора:
// 1 - Угловой точки p1
// 2 - Боковой прямой p1-p2
// 3 - Угловой прямой p2
// 4 - Боковой прямой p2-p3
// 5 - Угловой точки p3
// 6 - Боковой прямой p1-p3
// 7 - Внутренний