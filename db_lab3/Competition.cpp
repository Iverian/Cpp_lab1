#include "Competition.h"
#include "ui_Competition.h"

#include <QIntValidator>

int Useless::num(int oldData, QWidget* parent)
{
	Useless w(parent);
	int retval = -1;
	w.ui->lineEdit->setValidator(new QIntValidator(w.ui->lineEdit));
	if (oldData != -1)
		w.ui->lineEdit->setText(QString::number(oldData));
	if (w.exec() == QDialog::Accepted)
		retval = w.ui->lineEdit->text().toInt();
	return retval;
}

QString Useless::get(QStringList tip, QWidget* parent)
{
	Useless w(parent);
	auto comp = new QCompleter(tip);
	w.ui->lineEdit->setCompleter(comp);
	QString retval;
	if (w.exec() == QDialog::Accepted)
		retval = w.ui->lineEdit->text();
	delete comp;
	return retval;
}

Useless::Useless(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::Competition)
{
	ui->setupUi(this);
	setWindowTitle(" ");
}

Useless::~Useless() { delete ui; }
