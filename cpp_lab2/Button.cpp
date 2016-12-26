#include "Button.h"
#include "Symbol.h"

Button::Button(int id, QWidget *parent)
    : QToolButton(parent)
    , symbolId(id)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(Symbol::instance().at(id));
}

int Button::id() const{
    return symbolId;
}

QSize Button::sizeHint() const
{
    auto size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.rheight(), size.rwidth());
    return size;
}
