/********************************************************************************
** Form generated from reading UI file 'Nevajno_kak.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEVAJNO_KAK_H
#define UI_NEVAJNO_KAK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Nevajno_kakClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QListView *listView;
    QPushButton *pushButton;
    QTableView *tableView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Nevajno_kakClass)
    {
        if (Nevajno_kakClass->objectName().isEmpty())
            Nevajno_kakClass->setObjectName(QStringLiteral("Nevajno_kakClass"));
        Nevajno_kakClass->resize(1075, 579);
        centralWidget = new QWidget(Nevajno_kakClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(260, 490, 811, 61));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(5, 10, 251, 541));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 310, 811, 171));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(260, 10, 811, 291));
        Nevajno_kakClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Nevajno_kakClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Nevajno_kakClass->setStatusBar(statusBar);

        retranslateUi(Nevajno_kakClass);

        QMetaObject::connectSlotsByName(Nevajno_kakClass);
    } // setupUi

    void retranslateUi(QMainWindow *Nevajno_kakClass)
    {
        Nevajno_kakClass->setWindowTitle(QApplication::translate("Nevajno_kakClass", "Nevajno_kak", 0));
        pushButton->setText(QApplication::translate("Nevajno_kakClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Nevajno_kakClass: public Ui_Nevajno_kakClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEVAJNO_KAK_H
