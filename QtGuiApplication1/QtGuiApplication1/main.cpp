#include "MyMainWindow.h"
#include "SelectView.h"

#include <QApplication>
#include <QErrorMessage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
	QErrorMessage msg;
	SelectView sel;

	QObject::connect(&w, SIGNAL(emit_selectcur(const QSqlQuery&)), &sel, SLOT(get_msg(const QSqlQuery&)));
	QObject::connect(&w, SIGNAL(emit_alarm(const QString&)), &msg, SLOT(showMessage(const QString&)));

    w.show();
    return a.exec();
}
