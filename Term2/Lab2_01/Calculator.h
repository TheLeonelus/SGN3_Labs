#pragma once

#include <QtCore>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QLCDNumber>
#include <QtMath>
#include <QColorDialog>

#define PRECISION 0.000000001

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
    double sumInMemory;

public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str, const QColor col);
    QPushButton* createButtonOfUnaryOperator(const QString& str, const QColor col);
    void calculateBinaryOperation();
    void abortOperation();

public slots:
    void slotButtonClicked();
    void unaryOperatorButtonClicked();
};
