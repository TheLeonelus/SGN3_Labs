#include "Calculator.h"

Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    m_plcd = new QLCDNumber(20);
    m_plcd->setSegmentStyle(QLCDNumber::Flat); // Плиточный формат кнопок
    m_plcd->setMinimumSize(100, 50);
    int lines = 4, columns = 8;

    QString aButtons[lines][columns] = { {"sqrt(x)", "1/x", "sin(x)", "MR", "7", "8", "9", "/"},
                                         {"", "x!", "cos(x)", "MC", "4", "5", "6", "*"},
                                         {"", "x^2", "tg(x)", "M-", "1", "2", "3", "-"},
                                         {"", "x^3", "ctg(x)", "M+", "0", ".", "=", "+"} };

    // Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, columns);
    ptopLayout->addWidget(createButton("C"), 1, columns - 2);
    ptopLayout->addWidget(createButton("CE"), 1, columns - 1);

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        }
    }
    setLayout(ptopLayout);
    // ui.setupUi(this);
}

QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(50, 50);
    QObject::connect(pcmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
    return pcmd;
}

void Calculator::calculate()
{
    qreal dOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    qreal dOperand1 = m_stk.pop().toDouble();
    qreal dResult = 0;

    if (strOperation == "+") {
        dResult = dOperand1 + dOperand2;
        m_plcd->display(dResult);
    }
    if (strOperation == "-") {
        dResult = dOperand1 - dOperand2;
        m_plcd->display(dResult);
    }
    if (strOperation == "/") {
        if (dOperand2 < 0.00000001)
            m_plcd->display("NaN");
        else {
            dResult = dOperand1 / dOperand2;
            m_plcd->display(dResult);
        }
    }
    if (strOperation == "*") {
        dResult = dOperand1 * dOperand2;
        m_plcd->display(dResult);
    }
}

void Calculator::slotButtonClicked()
{
    QString str = ((QPushButton*)sender())->text();
    // Button CE pressed
    if (str == "CE") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str == "C") {
        m_strDisplay.chop(1);
        if (m_strDisplay.isEmpty()) {
                m_stk.clear();
                m_strDisplay = "";
                m_plcd->display("0");
                return;
        }
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str.contains(QRegularExpression("[0-9]"))) {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else {
        if (str == ".") {
        if (!m_strDisplay.endsWith("."))
            m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }
        else {
            if (m_stk.count() >= 2) {
                m_stk.push(QString().setNum(m_plcd->value()));
                calculate();
                m_stk.clear();
                m_stk.push(QString().setNum(m_plcd->value()));
                m_strDisplay = QString().setNum(m_plcd->value());
                if (str != "=") {
                    m_stk.push(str);
                }
            }
            else {
                m_stk.push(QString().setNum(m_plcd->value()));
                m_stk.push(str);
                m_strDisplay = "";
            }
        }
    }
}

