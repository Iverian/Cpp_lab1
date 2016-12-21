#pragma once

#include <ui_Nevajno_kak.h>
#include <QSqlQuery>
#include <QSqlQueryModel>

class MyMainWindow : public QMainWindow {
    Q_OBJECT
public:
    MyMainWindow(QWidget *parent = Q_NULLPTR);
private slots:
    void on_pushButton_clicked();
    void on_listView_clicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

signals:
    void emitError(QString errMsg);
private:
    Ui::Nevajno_kakClass ui;
	QSqlDatabase db;
};
