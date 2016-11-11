#include "Nevajno_kak.h"

#include <QSqlError>
#include <QSqlTableModel>
#include <QStringListModel>

Nevajno_kak::Nevajno_kak(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("file");
    db.open();
    ui.listView->setModel(new QStringListModel(db.tables()));
	ui.listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(button()));
	connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(button()));
    connect(ui.listView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(table_chose()));
}

void Nevajno_kak::button() const
{
    auto executedQuery = db.exec(ui.lineEdit->text());
    auto queryError = executedQuery.lastError();
    if (queryError.type() != QSqlError::NoError)
        emit_alarm(queryError.text());
    else {
        ui.lineEdit->clear();
		if (executedQuery.isSelect())
			emit_selectcur(executedQuery);
		else {
			auto currentIndex = db.tables().indexOf(ui.listView->selectionModel()->currentIndex().data().toString());
			ui.listView->setModel(new QStringListModel(db.tables()));
			connect(ui.listView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(table_chose()));
			ui.listView->selectionModel()->setCurrentIndex(ui.listView->model()->index(currentIndex, 0), QItemSelectionModel::SelectCurrent);
		}
    }
}

void Nevajno_kak::table_chose() const
{
    auto qr = ui.listView->selectionModel()->currentIndex().data().toString();
	auto model = new QSqlQueryModel();
	model->setQuery("select * from " + qr);
    ui.tableView->setModel(model);
}
