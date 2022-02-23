#pragma once

#include "ui_Calculator.h"

#include <QWidget>
#include <QApplication>
#include <QStack>
#include <QLCDNumber>
#include <QRegularExpression>

class QLCDNumber;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber* m_plcd;
    QLCDNumber* m_debug;
    QStack<QString> m_stk;
    QString         m_strDisplay;

public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();

public slots:
    void slotButtonClicked();
};
