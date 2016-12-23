#ifndef USELEES_H
#define USELEES_H

#include <QDialog>

namespace Ui {
class Uselees;
}

class Uselees : public QDialog
{
	Q_OBJECT

public:
	explicit Uselees(QWidget *parent = 0);
	~Uselees();

private:
	Ui::Uselees *ui;
};

#endif // USELEES_H
