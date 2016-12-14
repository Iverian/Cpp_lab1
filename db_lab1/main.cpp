#include "MyMainWindow.h"

#include <QApplication>
#include <QErrorMessage>
#include <windows.h>

int main(int argc, char** argv)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    QApplication a(argc, argv);
    MyMainWindow w;
    QErrorMessage e;
    QObject::connect(&w, SIGNAL(emitError(QString)), &e, SLOT(showMessage(QString)));
    w.show();
    return a.exec();
}
