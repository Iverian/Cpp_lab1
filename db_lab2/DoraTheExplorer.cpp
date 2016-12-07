#include "DoraTheExplorer.h"
#include "AddDatabaseDialog.h"
#include "ui_DoraTheExplorer.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStringListModel>

DoraTheExplorer::DoraTheExplorer(QWidget* parent)
	: QMainWindow(parent)
	, m_bases()
	, ui(new Ui::DoraTheExplorer)
{
	ui->setupUi(this);
}

DoraTheExplorer::~DoraTheExplorer()
{
	delete ui;
}

void DoraTheExplorer::on_dbList_clicked(const QModelIndex&)
{
	refreshTableList(true);
}

void DoraTheExplorer::on_addDb_clicked()
{
	auto database = AddDatabaseDialog::add(this);
	if (database.open())
		m_bases.append(database);
	refreshDbList(false);
}

void DoraTheExplorer::on_deleteDb_clicked()
{
	auto number = ui->dbList->currentIndex().row();
	m_bases[number].close();
	QSqlDatabase::removeDatabase(m_bases[number].connectionName());
	m_bases.erase(m_bases.begin() + number);
	refreshDbList(true);
}

void DoraTheExplorer::on_tableList_clicked(const QModelIndex&)
{
	refreshTableView();
}

void DoraTheExplorer::on_sendButton_clicked()
{
	auto query = activeDatabase().exec(ui->queryInput->toPlainText());
	auto error = query.lastError();
	if (error.type() != QSqlError::NoError)
		emit emitError(error.text());
	else {
		if (query.isSelect()) {
			auto model = new QSqlQueryModel;
			model->setQuery(query);
			ui->tableView->setModel(model);
		} else
			refreshTableList(false);
	}
}

QSqlDatabase DoraTheExplorer::activeDatabase()
{
	QSqlDatabase retval;
	auto index = ui->dbList->currentIndex().row();
	if (index != -1) {
		retval = m_bases[index];
		retval.open();
	}
	return retval;
}

QString DoraTheExplorer::activeTable()
{
	return ui->tableList->currentIndex().data().toString();
}

void DoraTheExplorer::refreshDbList(bool calledFromDelete)
{
	QStringList dbNames;
	for (auto& i : m_bases)
		dbNames.append(i.databaseName());
	auto activeDb = ui->dbList->currentIndex().data().toString();
	auto newIndex = calledFromDelete ? dbNames.indexOf(activeDb)
									 : ui->dbList->currentIndex().row();
	ui->dbList->setModel(new QStringListModel(dbNames));
	if (newIndex != -1)
		ui->dbList->setCurrentIndex(ui->dbList->model()->index(newIndex, 0));
	else
		refreshTableList(true);
}

void DoraTheExplorer::refreshTableList(bool databaseChanged)
{
	auto activeDb = activeDatabase();
	if (activeDb.isOpen()) {
		auto tables = activeDb.tables();
		auto currentTable = databaseChanged ? QString::null : activeTable();
		auto newIndex = databaseChanged ? -1 : tables.indexOf(currentTable);
		ui->tableList->setModel(new QStringListModel(tables));
		if (newIndex != -1)
			ui->tableList->setCurrentIndex(ui->tableList->model()->index(newIndex, 0));
		refreshTableView();
	}
}

void DoraTheExplorer::refreshTableView()
{
	auto activeDb = activeDatabase();
	if (activeDb.isOpen()) {
		auto model = new QSqlQueryModel();
		model->setQuery("SELECT * FROM " + activeTable(), activeDb);
		ui->tableView->setModel(model);
	}
}
