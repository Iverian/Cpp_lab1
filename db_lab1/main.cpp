#include "MyMainWindow.h"
#include <QApplication>
#include <QErrorMessage>
int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MyMainWindow w;
    QErrorMessage e;
    QObject::connect(&w, SIGNAL(emitError(QString)), &e, SLOT(showMessage(QString)));
    w.show();
    return a.exec();
}
