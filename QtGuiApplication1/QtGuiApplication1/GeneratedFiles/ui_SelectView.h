/********************************************************************************
** Form generated from reading UI file 'SelectView.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTVIEW_H
#define UI_SELECTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectView
{
public:
    QTableView *tableView;

    void setupUi(QWidget *SelectView)
    {
        if (SelectView->objectName().isEmpty())
            SelectView->setObjectName(QStringLiteral("SelectView"));
        SelectView->resize(232, 229);
        tableView = new QTableView(SelectView);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 231, 231));

        retranslateUi(SelectView);

        QMetaObject::connectSlotsByName(SelectView);
    } // setupUi

    void retranslateUi(QWidget *SelectView)
    {
        SelectView->setWindowTitle(QApplication::translate("SelectView", "SelectView", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectView: public Ui_SelectView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTVIEW_H
