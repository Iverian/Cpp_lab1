#pragma once

#include <QMainWindow>
#include <QVector>
#include <QSqlDatabase>

namespace Ui {
class DoraTheExplorer;
}

class DoraTheExplorer : public QMainWindow {
	Q_OBJECT

public:
	explicit DoraTheExplorer(QWidget* parent = 0);
	~DoraTheExplorer();
signals:
	void emitError(QString message);
private slots:
	void on_dbList_clicked(const QModelIndex&);
	void on_addDb_clicked();
	void on_deleteDb_clicked();
	void on_tableList_clicked(const QModelIndex&);
	void on_sendButton_clicked();

private:
	QSqlDatabase activeDatabase();
	QString activeTable();
	void refreshDbList(bool calledFromDelete);
	void refreshTableList(bool databaseChanged);
	void refreshTableView();

	QVector<QSqlDatabase> m_addedDb;
	Ui::DoraTheExplorer* ui;
};
