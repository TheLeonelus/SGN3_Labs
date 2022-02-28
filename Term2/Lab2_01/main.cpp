#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calculator;
    calculator.setWindowTitle("Calculator");
    calculator.resize(230, 200);
    calculator.setStyleSheet("background: black;");
    calculator.show();
    return a.exec();
}
