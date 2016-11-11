#include "SelectView.h"
#include <QSqlTableModel>

SelectView::SelectView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void SelectView::get_msg(QSqlQuery x)
{
	auto smth = new QSqlQueryModel();
	smth->setQuery(x);
	ui.tableView->setModel(smth);
	show();
}
