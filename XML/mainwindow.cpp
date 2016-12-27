#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

typedef QStandardItem QStandartItem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,SIGNAL(triggered(bool)),SLOT(OnOpenClicked()));
    connect(ui->actionClose_all,SIGNAL(triggered(bool)),SLOT(OnCloseAllClicked()));
    connect(ui->actionExit_2,SIGNAL(triggered(bool)),SLOT(OnExitClicked()));

    model = new QStandardItemModel(0,1,this); // 0 - rows  ; 1 - columns    if problems 1=2

    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::TransverseNode (const QDomNode& node)
{
    QStandardItem* fuckingroot = new QStandardItem(Filename);
    model->appendRow(fuckingroot);

    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if (domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull())
            {
                if (domElement.tagName()=="array")
                {
                    QStandardItem* Org = new QStandardItem("Наименование организации\t\t"+domElement.firstChildElement("Name").text());
                    fuckingroot->appendRow(Org);
                    Org->appendRow(new QStandardItem("Адрес\t\t\t\t"+domElement.firstChildElement("Address").text()));
                    Org->appendRow(new QStandardItem("Административный округ\t\t"+domElement.firstChildElement("AdmArea").text()));
                    Org->appendRow(new QStandardItem("Район\t\t\t\t"+domElement.firstChildElement("District").text()));
                    Org->appendRow(new QStandardItem("Телефон\t\t\t\t"+domElement.firstChildElement("PublicPhone").firstChildElement("PublicPhone").text()));
                    Org->appendRow(new QStandardItem("Кол-во посадочных мест\t\t"+domElement.firstChildElement("SeatsCount").text()));
                    QStandardItem* Geo = new QStandardItem("Геоданные");
                    Org->appendRow(Geo);
                    Geo->appendRow(new QStandardItem("Широта \t\t"+domElement.firstChildElement("Longitude_WGS84").text()));
                    Geo->appendRow(new QStandardItem("Долгота\t\t"+domElement.firstChildElement("Latitude_WGS84").text()));
                }
            }
        }
        domNode = domNode.nextSibling();
    }
}

void MainWindow::OnOpenClicked()
{
    Filename = QFileDialog().getOpenFileName(this, "", "D:\\xmlfiles");
    QDomDocument document;
    QFile file(Filename);
    if (file.open(QIODevice::ReadOnly))
    {
        if (document.setContent(&file))
        {
            QDomElement dom_el = document.documentElement();
            TransverseNode (dom_el);
        }
        file.close();
    }
}

void MainWindow::OnCloseAllClicked()
{
    model->clear();
}

void MainWindow::OnExitClicked()
{
    if (QMessageBox::question(this, "Выход", "Вы уверены ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        QApplication::exit();
    else
        throw 1;
}
