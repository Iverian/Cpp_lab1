#pragma once

#include <QObject>
#include <QtCore/QStringListModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>

class DbWrapper : public QObject {
    Q_OBJECT

public:
    explicit DbWrapper(QObject* parent = nullptr);
    explicit DbWrapper(QSqlDatabase& db, QObject* parent = nullptr);

    DbWrapper& setDatabase(QSqlDatabase& db);
    QSqlQueryModel* getCurTableModel() const;
    QStringListModel* getTableListModel() const;
	QString getDbName() const;
public slots:
    void slot_receiveSqlQuery(const QString& queryText);
	void slot_setCurTable(const QString& tableName);
signals:
	void emit_selectQuery(QSqlQueryModel* selectModel);
	void emit_refreshCurTable(QSqlQueryModel* tableModel);
	void emit_refreshTableList(QStringListModel* listModel, QString selectedTable);
	void emit_errMsg(const QString& error);
private:
    QSqlDatabase* m_database;
	QString m_curTable;
};
