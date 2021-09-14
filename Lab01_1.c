#include <stdio.h> // Header file

int xPointInput(int number);
int yPointInput(int number);
int rightPrint(void);
int leftPrint(void);
int includePrint(void);
int inappropriateInputPrint(void);
int sectorPrint(int n);
int isIncludeCheck(int x1, int x2, int x3, int y1, int y2, int y3);
int isSectorCheck(int x1, int x2, int x3, int y1, int y2, int y3);

void main()
{
    printf("Input number of points (assuming that points 1(Top),2(Right) <and 3(Left)> are apexes of the lines [3/4]: ");
    int n; // Number of points
    scanf("%d", &n);
    switch(n)
    {
        case 3: // Line-case
        {
            int array[4][3]; // Array with point-coordinates
            int k; // Cycle`s iteration | Number of point
            for (k=1; k<=3; ++k) { // fullfilling the array
            array[k][1]=xPointInput(k);
            array[k][2]=yPointInput(k);
            //printf("x %d", array[k][1]);
            //printf("y %d", array[k][2]);
        }
            switch(isIncludeCheck(array[1][1], array[2][1], array[3][1], array[1][2], array[2][2], array[3][2]))
            {
                case 0:
                {
                    if((array[1][1]==array[2][1]))
                    {
                        if(array[1][2]>array[2][2])
                        {
                            if(array[1][1]<array[3][1])
                            {
                                leftPrint();
                                break;
                            }
                            else
                            {
                                rightPrint();
                                break;
                            }
                        }
                        else
                        {
                            if(array[1][1]<array[3][1])
                            {
                                rightPrint();
                                break;
                            }
                            else
                            {
                                leftPrint();
                                break;
                            }
                        }
                    }
                    else
                    {
                        if((array[2][1]-array[1][1])>0)
                        {
                            if(array[3][2]<(((array[3][1]-array[2][1])*(array[1][2]-array[2][2]))/(array[1][1]-array[2][1])+array[2][2]))
                            {
                                rightPrint();
                                break;
                            }
                            else
                            {
                                leftPrint();
                                break;
                            }
                        }
                        else
                        {
                            if(array[3][2]<(((array[3][1]-array[2][1])*(array[1][2]-array[2][2]))/(array[1][1]-array[2][1])+array[2][2]))
                            {
                                leftPrint();
                                break;
                            }
                            else
                            {
                                rightPrint();
                                break;
                            }
                        }
                    }
                }
                case 1:
                {
                    inappropriateInputPrint(); // 1.2
                    break;
                }
                case 2:
                {
                    includePrint(); // 2.4
                    break;
                }
            }
        }
        case 4: // triangle-case
        {
            int array[5][3]; // Array with point-coordinates
            int k; // Cycle`s iteration | Number of point
            for (k=1; k<=4; ++k) // fullfilling the array
            {
                array[k][1]=point_x(k);
                array[k][2]=point_y(k);
                //printf("x %d", array[k][1]);
                //printf("y %d", array[k][2]);
            }
            switch(isIncludeCheck(array[1][1], array[2][1], array[3][1], array[1][2], array[2][2], array[3][2]))
            {
                case 1:
                {
                    inappropriateInputPrint(); // 1.2
                    break;
                }
                case 2:
                {
                    inappropriateInputPrint(); // 1.2
                    break;
                }
                case 0:
                {
                    if((isIncludeCheck(array[1][1], array[2][1], array[4][1], array[1][2], array[2][2], array[4][2])==0)&&(isIncludeCheck(array[2][1], array[3][1], array[4][1], array[2][2], array[3][2], array[4][2])==0)&&(isIncludeCheck(array[1][1], array[3][1], array[4][1], array[1][2], array[3][2], array[4][2])==0))
                    {
                        if(isSectorCheck(array[1][1], array[3][1], array [4][1], array[1][2], array[3][2], array[4][2])==1)
                        {
                            if(isSectorCheck(array[1][1], array[2][1], array [4][1], array[1][2], array[2][2], array[4][2])==1)
                            {
                                sectorPrint(1); // 3.1.1
                                break;
                            }
                            else
                            {
                                if(isSectorCheck(array[2][1], array[3][1], array [4][1], array[2][2], array[3][2], array[4][2])==1)
                                {
                                    sectorPrint(6); // 3.1.6
                                    break;
                                }
                                else 
                                {
                                    sectorPrint(5); // 3.1.5
                                    break;
                                }
                            } 
                        }
                        else
                        {
                            if(isSectorCheck(array[1][1], array[2][1], array [4][1], array[1][2], array[2][2], array[4][2])==1)
                            {
                                if(isSectorCheck(array[2][1], array[3][1], array [4][1], array[2][2], array[3][2], array[4][2])==1)
                                {
                                    sectorPrint(2); // 3.1.2
                                    break;
                                }
                                else
                                {
                                    sectorPrint(3); // 3.1.3
                                    break;
                                }
                            }
                            else
                            {
                                if(isSectorCheck(array[2][1], array[3][1], array [4][1], array[2][2], array[3][2], array[4][2])==1) // 23
                                {
                                    sectorPrint(7); // 3.1.7
                                    break;
                                }
                                else 
                                {
                                    sectorPrint(4); // 3.1.4
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        includePrint(); // 2.4
                        break;
                    }
                }
            }          
        }
    }
}

int xPointInput(int number) // Number of point
{
    int coord;  // Input of X-coord
    printf("\nInput point %i%s%i%s",number, ":\nx", number, ": ");
    scanf("%i", &coord);
    //printf("%i", coord);
    return coord;
}

int yPointInput(int number) // Number of point
{
    int coord;  // Input of Y-coord
    printf("\ny%i%s", number, ": ");
    scanf("%i", &coord);
    //printf("%i", coord);
    return coord;
}

int rightPrint(void) // 2.3.2 output
{
    printf("\nPoint is to the right side from vector (p1,p2)."); // 2.3.2
}

int leftPrint(void) // 2.3.1 output
{
    printf("\nPoint is to the left side from vector (p1,p2)."); // 2.3.1
}

int includePrint(void) // 2.4 output
{
    printf("\nLine includes the point.");
}

int inappropriateInputPrint(void) // 1.2/2.4
{
    printf("Inappropriate input!");
}

int sectorPrint(int n) // 3.1 output
{
    printf("\nPoint is in the №%i%s", n, " sector."); // 3.1
}

int isIncludeCheck(int x1, int x2, int x3, int y1, int y2, int y3) // Matching points check
{
    int n;
    if((x1==x2)&&(y1==y2)) n = 1; // 1.2
    else 
    {
        if(((x1==x2)&&(x2==x3))||(((y1==y2)&&(y2==y3))||(y3==((x3-x2)*(y1-y2))/(x1-x2)+y2))) n = 2; // 2.4.1
        else n = 0;
    }
    return n;
}

int isSectorCheck(int x1, int x2, int x3, int y1, int y2, int y3) // y comparision  
{
    int n;
    if(y3>((x3-x2)*(y1-y2)/(x1-x2)+y2)) n = 1;
    else n = 0;
    return n;
}

//
// 1.1 - Неверное количество точек
// 1.2 - Вершины совпадают
// 2.3.1 - Точка слева от вектора (p1,p2)
// 2.3.2 - Точка справа от вектора (p1,p2)
// 2.4 - Точка принадлежит линии
// 2.4.1 - 3 точки лежат на одной прямой
// 3.1.1 - 1 сектор
// 3.1.2 - 2 сектор
// 3.1.3 - 3 сектор
// 3.1.4 - 4 сектор
// 3.1.5 - 5 сектор
// 3.1.6 - 6 сектор
// 3.1.7 - 7 сектор
// ____________________________________
// Сектора:
// 1 - Угловой точки p1
// 2 - Боковой прямой p1-p2
// 3 - Угловой прямой p2
// 4 - Боковой прямой p2-p3
// 5 - Угловой точки p3
// 6 - Боковой прямой p1-p3
// 7 - Внутренний