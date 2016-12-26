#include "Symbol.h"
#include "utility.h"

#define add(tok_id, str) (mapper.insert(tok_id,(str)))

const Symbol& Symbol::instance()
{
    static const Symbol inst;
    return inst;
}

const QString& Symbol::at(int index) const
{
    return instance().mapper.at(index);
}

int Symbol::indexOf(const QString &symbol) const
{
    return instance().mapper.indexOf(symbol);
}

Symbol::Symbol()
    : mapper()
{
    for (auto i = 0; i != id::magicNumber; ++i)
        mapper.push_back(QString::number(i));
    add(TOK::CLEAR, "C");
    add(TOK::POINT, ".");
    add(TOK::EQUAL, "=");
    add(TOK::CHANGE_SIGN, ws(L"\x00b1"));
    add(TOK::INVERSE, "1/x");
    add(TOK::SQROOT, ws(L"\x221a"));
    add(TOK::DIV, ws(L"\x00f7"));
    add(TOK::MULT, ws(L"\x00d7"));
    add(TOK::MINUS, ws(L"\x2212"));
    add(TOK::PLUS, "+");
    add(TOK::SQUARE, ws(L"x\x00b2"));
    add(TOK::CUBE, ws(L"x\x00b3"));
    add(TOK::POWER, "^");
    add(TOK::ROOT, ws(L"y\x221ax"));
    add(TOK::EXP, "exp");
    add(TOK::LN, "ln");
    add(TOK::LOG, "log");
    add(TOK::CUBEROOT, ws(L"3\x221a"));
    add(TOK::SIN, "sin");
    add(TOK::COS, "cos");
    add(TOK::TAN, "tan");
    add(TOK::PI, ws(L"\x03c0"));
    add(TOK::SINH, "sinh");
    add(TOK::COSH, "cosh");
    add(TOK::TANH, "tanh");
    add(TOK::FACT, "n!");
}
