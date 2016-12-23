#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class ShowDialog;
}

class ShowDialog : public QDialog
{
	Q_OBJECT

public:
	static void showQuery(QSqlQuery query, QWidget* parent = 0);
	explicit ShowDialog(QWidget *parent = 0);
	~ShowDialog();

private:
	Ui::ShowDialog *ui;
};

#endif // SHOWDIALOG_H
