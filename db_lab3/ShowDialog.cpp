#include "ShowDialog.h"
#include "ui_ShowDialog.h"

#include <QSqlQueryModel>

void ShowDialog::showQuery(QSqlQuery query, QWidget* parent)
{
	ShowDialog w(parent);
	auto model = new QSqlQueryModel(parent);
	model->setQuery(query);
	w.ui->tableView->setModel(model);
	w.exec();
}

ShowDialog::ShowDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::ShowDialog)
{
	ui->setupUi(this);
}

ShowDialog::~ShowDialog() { delete ui; }
