#include "MainWindow.h"

#include <QtWidgets/QApplication>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	auto myDb = QSqlDatabase::addDatabase("QSQLITE");
	myDb.setDatabaseName("GHOSTBUSTERS.db");
	myDb.open();

    w.show();

    return a.exec();
}
