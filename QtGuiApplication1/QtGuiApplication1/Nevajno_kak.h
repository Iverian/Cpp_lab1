#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_Nevajno_kak.h>
#include <QSqlDatabase>
#include <QSqlQuery>

class Nevajno_kak : public QMainWindow
{
    Q_OBJECT
public:
    Nevajno_kak(QWidget *parent = Q_NULLPTR);
public slots:
	void button() const;
	void table_chose() const;
signals:
	void emit_selectcur(QSqlQuery query) const;
	void emit_alarm(const QString& smth_bad) const;
private:
    Ui::Nevajno_kakClass ui;
	QSqlDatabase db;
};
