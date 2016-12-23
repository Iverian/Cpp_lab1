#include "MemberModify.h"
#include "ui_MemberModify.h"

#include <QDebug>

void MemberModify::modify(QWidget* parent, int id) {
	qDebug() << id;
}

MemberModify::MemberModify(QWidget* parent, int id)
	: QDialog(parent)
	, m_id(id)
	, ui(new Ui::MemberModify)
{
	ui->setupUi(this);
}

MemberModify::~MemberModify() { delete ui; }
