#include "DoraTheExplorer.h"

#include <QApplication>
#include <QErrorMessage>
#include <windows.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	DoraTheExplorer w;
	QErrorMessage e;
	e.setModal(true);
	QObject::connect(&w, SIGNAL(emitError(QString)), &e, SLOT(showMessage(QString)));
	w.show();

	return a.exec();
}
