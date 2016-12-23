#include "MainWindow.h"

#include <QApplication>
#include <QErrorMessage>
#include <QSqlDatabase>
#include <windows.h>

void initDatabase();

int main(int argc, char* argv[])
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	QApplication a(argc, argv);
	MainWindow w;
	QErrorMessage e;
	QObject::connect(&w, SIGNAL(error(QString)), &e, SLOT(showMessage(QString)));
	w.show();
	initDatabase();
	return a.exec();
}

void initDatabase()
{
	auto db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName("195.19.32.74");
	db.setPort(5432);
	db.setDatabaseName("fn1131_2016");
	db.setUserName("student");
	db.setPassword("bmstu");
	db.open();
}
