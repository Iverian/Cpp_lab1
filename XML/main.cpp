#include "mainwindow.h"
#include <QApplication>

#include <QtXmlPatterns>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile Doc("rest.xml");
    QFile xqfile("_kermit.xq");
    Doc.open(QIODevice::ReadOnly);
    xqfile.open(QIODevice::ReadOnly);
    QString strquery = xqfile.readAll();
    qDebug()<<strquery;
    xqfile.close();

    QXmlQuery query;
    query.bindVariable("Doc", &Doc);
    query.setQuery(strquery);
    query.evaluateTo(&strquery);

    QMessageBox mb;
    qDebug() << strquery;
    mb.setText(strquery);
    mb.show();
    Doc.close();

    MainWindow w;
    w.show();

    return a.exec();
}
