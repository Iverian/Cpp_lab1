#include "DbWrapper.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>

DbWrapper::DbWrapper(QObject* parent)
    : QObject(parent)
    , m_database()
    , m_curTable()
{
}

DbWrapper::DbWrapper(QSqlDatabase& db, QObject* parent)
    : QObject(parent)
    , m_database(&db)
    , m_curTable()
{
}

DbWrapper& DbWrapper::setDatabase(QSqlDatabase& db)
{
    m_database = &db;
    return *this;
}

QSqlQueryModel* DbWrapper::getCurTableModel() const
{
    auto retval = new QSqlQueryModel();
    retval->setQuery(m_database->exec("select * from " + m_curTable));
    return retval;
}

QStringListModel* DbWrapper::getTableListModel() const
{
    return new QStringListModel(m_database->tables());
}

QString DbWrapper::getDbName() const
{
    return m_database->databaseName();
}

void DbWrapper::slot_receiveSqlQuery(const QString& queryText)
{
    auto query = m_database->exec(queryText);
    if (query.isSelect()) {
        auto selModel = new QSqlQueryModel;
        selModel->setQuery(query);
        emit emit_selectQuery(selModel);
    }
	else
		emit emit_refreshTableList(getTableListModel(), m_curTable);
}

void DbWrapper::slot_setCurTable(const QString& tableName)
{
	m_curTable = tableName;
	emit emit_refreshCurTable(getCurTableModel());
}
