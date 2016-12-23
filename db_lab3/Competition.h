#ifndef COMPETITION_H
#define COMPETITION_H

#include <QDialog>
#include <QCompleter>

namespace Ui {
class Competition;
}

class Useless : public QDialog
{
	Q_OBJECT
public:
	static int num(int oldData = -1, QWidget* parent = 0);
	static QString get(QStringList tip, QWidget* parent = 0);
	explicit Useless(QWidget *parent = 0);
	~Useless();

private:
	Ui::Competition *ui;
};

#endif // COMPETITION_H
