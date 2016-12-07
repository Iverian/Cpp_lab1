#include "AddDatabaseDialog.h"
#include "ui_AddDatabaseDialog.h"

#include <QPushButton>
#include <QSqlDatabase>

int AddDatabaseDialog::m_count(0);

AddDatabaseDialog::AddDatabaseDialog(QWidget* parent)
	: QDialog(parent)
	, m_check{false, true}
	, ui(new Ui::AddDatabaseDialog)
{
	ui->setupUi(this);
	for (const auto& i : QSqlDatabase::drivers())
		ui->driverBox->addItem(i);
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

QSqlDatabase AddDatabaseDialog::add(QWidget* parent)
{
	AddDatabaseDialog x(parent);
	QSqlDatabase retval;
	if (x.exec() == QDialog::Accepted) {
		auto connectionName = QString::number(m_count);
		retval
			= QSqlDatabase::addDatabase(x.ui->driverBox->currentText(), connectionName);

		retval.setHostName(x.ui->host->text());
		retval.setPort(x.ui->port->text().toInt());
		retval.setDatabaseName(x.ui->databaseName->text());
		retval.setUserName(x.ui->user_name->text());
		retval.setPassword(x.ui->pass->text());

		if (!retval.open())
			retval = QSqlDatabase();
		else {
			m_count++;
			retval.close();
		}
	}
	return retval;
}

AddDatabaseDialog::~AddDatabaseDialog()
{
	delete ui;
}

void AddDatabaseDialog::on_databaseName_editingFinished()
{
	m_check[0] = !ui->databaseName->text().isEmpty();
	activateOk();
}

void AddDatabaseDialog::on_port_editingFinished()
{
	auto text = ui->port->text();
	if (text.isEmpty())
		m_check[1] = true;
	else
		text.toInt(&m_check[1]);
	activateOk();
}

void AddDatabaseDialog::activateOk()
{
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_check[0] && m_check[1]);
}
