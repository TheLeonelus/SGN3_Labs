#include "Calculator.h"

Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
  //const QChar MathSymbolSquareRoot((QChar) 0x221A);

    m_plcd = new QLCDNumber(16); // Electronic display
    m_plcd->setSegmentStyle(QLCDNumber::Flat); // Tiled format of buttons
    m_plcd->setMinimumSize(120, 40);
    int lines = 4, columns = 8, unaryOpColumns = columns - 5;
    //Array of string buttons
    QString aButtons[lines][columns] = { {"sqrt(x)", "1/x"        , "sin(x)", "MR", "7", "8", "9", "\302\261"},
                                         {""       , "MS"         , "cos(x)", "MC", "4", "5", "6", "\303\227"},
                                         {""       , "x\302\262"  , "tg(x)" , "M-", "1", "2", "3", "-"       },
                                         {""       , "x\302\263"  , "ctg(x)", "M+", "0", ".", "=", "+"       }
                                       };

    // Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 1, 1, columns - 2);
    QColor col = QColor(75, 140, 255, 150);
    ptopLayout->addWidget(createButton("C", col), 1, columns - 2);
    ptopLayout->addWidget(createButton("CE", col), 1, columns - 1);
    // QPushButton creation and connect
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j <= unaryOpColumns; ++j) {
            QColor col = QColor(255, 196, 148, 100);
            ptopLayout->addWidget(createButtonOfUnaryOperator(aButtons[i][j], col), i + 2, j);
        }
        for (int j = unaryOpColumns + 1; j < columns; ++j) {
            QColor col = QColor(150, 215, 255, 100);
            ptopLayout->addWidget(createButton(aButtons[i][j], col), i + 2, j);
        }
    }
    setLayout(ptopLayout);
    // ui.setupUi(this);
}



// Buttons except unary operators creating from string name
QPushButton* Calculator::createButton(const QString& str, const QColor col)
{
    QPushButton* pcmd = new QPushButton(str);
    if(col.isValid()) {
       QString qss = QString("QPushButton { background-color: %1 ; margin: 1px ; border: 0px ;}").arg(col.name());
       pcmd->setStyleSheet(qss);
    }
    pcmd->setMinimumSize(50, 50);
    QObject::connect(pcmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
    return pcmd;
}


// Buttons for unary operators creating from string name
QPushButton* Calculator::createButtonOfUnaryOperator(const QString& str, const QColor col)
{
    QPushButton* pcmd = new QPushButton(str);
    if(col.isValid()) {
     // QString qss = QString("QPushButton:pressed { background-color: rgba(0,0,148,100) ; margin: 1px ; border: 0px; } ; QPushButton:released {background-color: rgba(150,196,148,100) ; margin: 1px ; border: 0px ; }").arg(col.name());
        QString qss = QString("QPushButton { background-color: %1 ; margin: 1px ; border: 0px ;}").arg(col.name());
        pcmd->setStyleSheet(qss);
    }
    pcmd->setMinimumSize(50, 50);
    QObject::connect(pcmd, &QPushButton::clicked, this, &Calculator::unaryOperatorButtonClicked);
    return pcmd;
}



void Calculator::slotButtonClicked()
{
    QString str = ((QPushButton*)sender())->text();
    // Button CE pressed
    if (str == "CE") {
        abortOperation();
        return;
    }
    // Button C pressed
    if (str == "C") {
        // if(!str.contains(QRegularExpression("0&"))) ?????
            m_strDisplay.chop(1);
        if (m_strDisplay.isEmpty()) {
                abortOperation();
                return;
        }
        m_plcd->display(m_strDisplay);
        return;
    }
    // Button *number* pressed
    if (str.contains(QRegularExpression("[0-9]"))) {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else {
        // Button . pressed
        if (str == ".") {
            if (!m_strDisplay.endsWith("."))
                m_strDisplay += str;
            m_plcd->display(m_strDisplay.toDouble());
        }
        else {
            // Binary operator pressed
            if (m_stk.count() >= 2) {
                m_stk.push(QString().setNum(m_plcd->value()));
                calculateBinaryOperation();
                m_stk.clear();
                m_stk.push(QString().setNum(m_plcd->value()));
                m_strDisplay = QString().setNum(m_plcd->value());
                if (str != "=") {
                    m_stk.push(str);
                }
            }
            else {

                if(str == "=")
                    return;
                m_stk.push(QString().setNum(m_plcd->value()));
                m_stk.push(str);
                m_strDisplay = "0";
                m_plcd->display("0");

            }
        }
    }
}



void Calculator::unaryOperatorButtonClicked()
{
    QString strOperation = ((QPushButton*)sender())->text();

    // Button Memory Save pressed
    if (strOperation == "MS") {
        sumInMemory = m_plcd->value();
        return;
    }

    // Button Memory Clear pressed
    if (strOperation == "MC")
        sumInMemory = 0;

    // Button Memory Addition pressed
    if (strOperation == "M+") {
        sumInMemory += m_plcd->value();
        return;
    }

    // Button Memory Subtraction pressed
    if (strOperation == "M-") {
        sumInMemory -= m_plcd->value();
        return;
    }
    // Button Memory Recall pressed
    if (strOperation == "MR")
        m_strDisplay = QString().setNum(sumInMemory);

    if (m_strDisplay.isEmpty() == false) {
        if (true) {
            m_stk.push(QString().setNum(m_plcd->value()));
            double dResult = 0;
            double dOperand = m_stk.pop().toDouble();

            //Button square root pressed
            if (strOperation == "sqrt(x)") {
                if (dOperand < PRECISION) {
                    abortOperation();
                    return;
                }
                dResult = sqrt(dOperand);
            }

            // Button reverse number pressed
            if (strOperation == "1/x") {
                if (dOperand < PRECISION) {
                    abortOperation();
                    return;
                }
                dResult = 1.0 / dOperand;
            }

            /*
            // Button factorial pressed
            if (strOperation == "x!") {
                std::round(dOperand);
                int intOperand = (int) dOperand;
                dResult = 1;
                for(int i = 1; i < intOperand; ++i)
                    dResult = dResult * (i + 1);
            }
            */

            // Button power to 2 pressed
            if (strOperation == "x\302\262")
                dResult = std::pow(dOperand, 2.0);

            // Button power to 3 pressed
            if (strOperation == "x\302\263")
                dResult = std::pow(dOperand, 3.0);

            // Button sin pressed
            if (strOperation == "sin(x)")
                dResult = sin(dOperand);

            // Button cos pressed
            if (strOperation == "cos(x)")
                dResult = cos(dOperand);

            // Button tg pressed
            if (strOperation == "tg(x)") {
                if(dOperand != cos(dOperand))
                    dResult = sin(dOperand) / cos(dOperand);
                else
                    abortOperation();
            }

            // Button ctg pressed
            if (strOperation == "ctg(x)") {
                if(dOperand != sin(dOperand))
                    dResult = cos(dOperand) / sin(dOperand);
                else
                    abortOperation();
            }

            // Button Memory Recall pressed
            if (strOperation == "MR")
                dResult = sumInMemory;
            m_plcd->display(dResult);
            m_stk.push(QString().setNum(m_plcd->value()));
            m_strDisplay = QString().setNum(m_plcd->value());
        }
    }
}




void Calculator::calculateBinaryOperation()
{
    qreal dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    qreal dOperand1 = m_stk.pop().toDouble();
    qreal dResult = 0;

    if (strOperation == "+")
        dResult = dOperand1 + dOperand2;
    if (strOperation == "-")
        dResult = dOperand1 - dOperand2;
    if (strOperation == "\302\261") {
        if (dOperand2 < PRECISION)
            dResult = 0;
        else
            dResult = dOperand1 / dOperand2;
    }
    if (strOperation == "\303\227")
        dResult = dOperand1 * dOperand2;
    m_plcd->display(dResult);
}

void Calculator::abortOperation()
{
    if(!m_stk.isEmpty())
        m_stk.clear();
    m_strDisplay = "";
    m_plcd->display("0");
}
