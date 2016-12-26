#pragma once

#include "properties.h"

#include <QString>
#include <QVector>

#define TOK (int)token

enum class token : int {
    CLEAR = id::magicNumber,
    POINT,
    EQUAL,
    CHANGE_SIGN,

    INVERSE,
    SQROOT,

    DIV,
    MULT,
    MINUS,
    PLUS,

    SQUARE,
    CUBE,
    POWER,
    ROOT,

    EXP,
    LN,
    LOG,
    CUBEROOT,

    SIN,
    COS,
    TAN,
    PI,

    SINH,
    COSH,
    TANH,
    FACT
};

struct Symbol {
    static const Symbol& instance();
    const QString& at(int index) const;
    int indexOf(const QString& symbol) const;
private:
    Symbol();
    QVector<QString> mapper;
};

