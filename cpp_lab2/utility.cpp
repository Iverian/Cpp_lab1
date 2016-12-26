#include "utility.h"
#include "Symbol.h"

#include <QtGlobal>

double applyBinary(double a, double b, int operId) {
    double retval = 0.;
    switch(operId) {
    case TOK::PLUS:
        retval = a + b;
        break;
    case TOK::MINUS:
        retval = a - b;
        break;
    case TOK::MULT:
        retval = a * b;
        break;
    case TOK::DIV:
        retval = a / b;
        break;
    case TOK::POWER:
        retval = pow(a, b);
        break;
    case TOK::ROOT:
        retval = pow(a, 1./b);
        break;
    case TOK::LOG:
        retval = log(a)/log(b);
        break;
    default:
        break;
    }
    return retval;
}

double fact(double num)
{
    double retval = num;
    if (qFuzzyCompare(num, round(num))) {
        int x = int(abs(num));
        retval = 1.;
        for (int i = 2; i < x; ++i)
            retval *= i;
    }
    return retval;
}

QString ws(const wchar_t* const string)
{
	return QString::fromWCharArray(string);
}

QString s(const char* const string)
{
	return QString(string);
}
