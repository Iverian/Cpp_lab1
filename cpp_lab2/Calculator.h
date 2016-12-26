#pragma once

#include "Button.h"
#include "properties.h"

#include <QWidget>
#include <QLCDNumber>
#include <QGroupBox>

struct QLCDKostil : QLCDNumber {
    using QLCDNumber::QLCDNumber;
    QSize sizeHint() const override;
};

class Calculator : public QWidget
{
    Q_OBJECT
    enum class mode : int
    {
        NORMAL = 0,
        ENGINEER = 1
    };

    static constexpr auto maxPrior = 3;
    static int binaryPrior(int operId);
    struct Pair {
        double num;
        int operId;
    };
    struct Internal
    {
        static constexpr auto stackSize = maxPrior + 1;
        Internal();
        Pair& cur();
        Pair& at(int id);
        void pop();
        void eval();
        void fetchLeftOperand();
        void push();
        bool empty();
        Pair stack[stackSize];
        int curPrior;
    };

public:
    explicit Calculator(QWidget *parent = Q_NULLPTR);
signals:
    void display(double number);
private slots:
    void changeMode(int modeId);

    void point();
    void equal();
    void clear();
    void unary();
    void binary();
    void digit();
    void changeSign();

private:
    void setupLayout();

    QWidget* setupEngButtons();
    QWidget *setupBaseButtons();

    Button* createButton(int id, const char* slot);
    QString windowTitle(mode id) const;

    Internal data;
    bool expectingOperator;

    mode current;
    QLCDKostil* resultDisplay;
    QGroupBox* buttonBox;
    QWidget* clearButton;
    QWidget* baseButtons;
    QWidget* engButtons;
};

