#pragma once

#include <QWidget>
#include <ui_SelectView.h>
#include <QSqlQuery>

class SelectView : public QWidget
{
	Q_OBJECT

public:
	SelectView(QWidget *parent = Q_NULLPTR);
	public slots:
	void get_msg(QSqlQuery x);

private:
	Ui::SelectView ui;
};
