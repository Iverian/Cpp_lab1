#pragma once

#include <QSqlQuery>
#include <ui_SelectView.h>

class SelectView : public QWidget {
    Q_OBJECT
public:
    SelectView(QWidget* parent = Q_NULLPTR);
public slots:
    void get_msg(const QSqlQuery& x);

private:
    Ui::SelectView ui;
};
