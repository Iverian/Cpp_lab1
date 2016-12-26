#pragma once

#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
public:
    Button(int id, QWidget* parent = Q_NULLPTR);
    int id() const;
    QSize sizeHint() const override;
private:
    int symbolId;
};
