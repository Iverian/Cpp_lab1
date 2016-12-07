#pragma once

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class AddDatabaseDialog;
}

class AddDatabaseDialog : public QDialog {
	Q_OBJECT

public:
	static QSqlDatabase add(QWidget* parent = 0);
	~AddDatabaseDialog();

private slots:
	void on_databaseName_editingFinished();

	void on_port_editingFinished();

private:
	explicit AddDatabaseDialog(QWidget* parent = 0);
	void activateOk();

	static int m_count;

	bool m_check[2];
	Ui::AddDatabaseDialog* ui;
};
