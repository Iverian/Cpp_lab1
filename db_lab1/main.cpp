<<<<<<< HEAD
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

=======
#include "MyMainWindow.h"
#include <QApplication>
#include <QErrorMessage>
int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MyMainWindow w;
    QErrorMessage e;
    QObject::connect(&w, SIGNAL(emitError(QString)), &e, SLOT(showMessage(QString)));
    w.show();
>>>>>>> ANEU_loader
    return a.exec();
}
