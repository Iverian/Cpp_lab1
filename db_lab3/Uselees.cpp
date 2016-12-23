#include "Uselees.h"
#include "ui_Uselees.h"

Uselees::Uselees(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Uselees)
{
	ui->setupUi(this);
}

Uselees::~Uselees()
{
	delete ui;
}
