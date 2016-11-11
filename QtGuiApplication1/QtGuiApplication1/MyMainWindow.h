#pragma once

#include <ui_Nevajno_kak.h>
#include <QSqlQuery>

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MyMainWindow(QWidget *parent = Q_NULLPTR);
public slots:
	void button() const;
	void table_chose() const;
signals:
	void emit_selectcur(const QSqlQuery& query) const;
	void emit_alarm(const QString& smth_bad) const;
private:
    Ui::Nevajno_kakClass ui;
	QSqlDatabase db;
};
