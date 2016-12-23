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
	, m_addedDb()
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
		m_addedDb.append(database);
	refreshDbList(false);
}

void DoraTheExplorer::on_deleteDb_clicked()
{
	auto number = ui->dbList->currentIndex().row();
	m_addedDb[number].close();
	QSqlDatabase::removeDatabase(m_addedDb[number].connectionName());
	m_addedDb.erase(m_addedDb.begin() + number);
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
			ui->tableList->setCurrentIndex(ui->tableList->model()->index(-1, 0));
			ui->tableView->setModel(model);
			ui->tableName->setText("SELECT");
		} else
			refreshTableList(false);
	}
}

QSqlDatabase DoraTheExplorer::activeDatabase()
{
	QSqlDatabase retval;
	auto index = ui->dbList->currentIndex().row();
	if (index != -1) {
		retval = m_addedDb[index];
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
	for (auto& i : m_addedDb)
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
	else
		ui->tableList->setModel(nullptr);
}

void DoraTheExplorer::refreshTableView()
{
	auto activeDb = activeDatabase();
	auto activeTbl = activeTable();
	if (activeDb.isOpen() && !activeTbl.isEmpty()) {
		auto model = new QSqlQueryModel();
		model->setQuery("SELECT * FROM " + activeTbl, activeDb);
		ui->tableView->setModel(model);
		ui->tableName->setText(activeDb.databaseName() + "." + activeTbl);
	}
	else {
		ui->tableView->setModel(nullptr);
		ui->tableName->setText("NO TABLE");
	}
}

void DoraTheExplorer::on_pushButton_3_clicked()
{
	auto query = activeDatabase().exec("with member_rating as(select x.id_member, y.rating from choir_members as x, competitions as y where x.id_choir=y.id_choir ), member_max as ( select id_member from member_rating group by id_member having sum(rating) >= all(select sum(rating) from member_rating group by id_member) )select name from members where id in (select id_member from member_max);");
	auto error = query.lastError();
	if (error.type() != QSqlError::NoError)
		emit emitError(error.text());
	else {
		if (query.isSelect()) {
			auto model = new QSqlQueryModel;
			model->setQuery(query);
			ui->tableList->setCurrentIndex(ui->tableList->model()->index(-1, 0));
			ui->tableView->setModel(model);
			ui->tableName->setText("SELECT");
		} else
			refreshTableList(false);
	}
}

void DoraTheExplorer::on_pushButton_clicked()
{
	auto query = activeDatabase().exec("with member_rating as(select x.id_member, y.rating from choir_members as x, competitions as y where x.id_choir=y.id_choir ), member_min as ( select id_member from member_rating group by id_member having sum(rating) <= all(select sum(rating) from member_rating group by id_member) )select name from members where id in (select id_member from member_min);");
	auto error = query.lastError();
	if (error.type() != QSqlError::NoError)
		emit emitError(error.text());
	else {
		if (query.isSelect()) {
			auto model = new QSqlQueryModel;
			model->setQuery(query);
			ui->tableList->setCurrentIndex(ui->tableList->model()->index(-1, 0));
			ui->tableView->setModel(model);
			ui->tableName->setText("SELECT");
		} else
			refreshTableList(false);
	}
}

void DoraTheExplorer::on_pushButton_2_clicked()
{
	auto query = activeDatabase().exec("with member_rating as(select x.id_member, y.rating from choir_members as x, competitions as y where x.id_choir=y.id_choir) select id_member, sum(rating) from member_rating group by id_member order by id_member asc;");
	auto error = query.lastError();
	if (error.type() != QSqlError::NoError)
		emit emitError(error.text());
	else {
		if (query.isSelect()) {
			auto model = new QSqlQueryModel;
			model->setQuery(query);
			ui->tableList->setCurrentIndex(ui->tableList->model()->index(-1, 0));
			ui->tableView->setModel(model);
			ui->tableName->setText("SELECT");
		} else
			refreshTableList(false);
	}
}
