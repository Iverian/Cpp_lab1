#include "MyMainWindow.h"

#include <QStringListModel>
#include <QSqlError>

MyMainWindow::MyMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName("195.19.32.74");
	db.setUserName("student");
	db.setPassword("bmstu");
    db.setDatabaseName("fn1131_2016");
	if (!db.open()) {
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName("xui");
		db.open();
	}
	ui.listView->setModel(new QStringListModel(db.tables()));
}

void MyMainWindow::on_pushButton_clicked()
{
	auto executedQuery = db.exec(ui.queryInput->toPlainText());
    auto error = executedQuery.lastError();
    if (error.type() != QSqlError::NoError)
        emit emitError(error.text());
    else {
        auto model = new QSqlQueryModel;
        if (executedQuery.isSelect())
            model->setQuery(executedQuery);
        else {
            auto activeTable = ui.listView->currentIndex().data().toString();
            auto newIndex = db.tables().indexOf(activeTable);
            ui.listView->setModel(new QStringListModel(db.tables()));
            if (newIndex != -1) {
                model->setQuery("select * from " + activeTable, db);
                ui.listView->setCurrentIndex(ui.listView->model()->index(newIndex, 0));
            }
        }
        ui.tableView->setModel(model);
    }
}

void MyMainWindow::on_listView_clicked(const QModelIndex &index)
{
    auto model = new QSqlQueryModel;
    model->setQuery("select * from " + index.data().toString(), db);
    ui.tableView->setModel(model);
}

void MyMainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}
