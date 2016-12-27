#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QtXml>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMessageBox>


namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OnOpenClicked();
    void OnCloseAllClicked();
    void OnExitClicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *model;
    QString Filename;

    void TransverseNode(const QDomNode&);
};

#endif // MAINWINDOW_H
