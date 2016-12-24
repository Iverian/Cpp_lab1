#include "ModifyDialog.h"
#include "ui_ModifyDialog.h"

#include <QPushButton>
#include <QVBoxLayout>

ModifyDialog::ModifyDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::ModifyDialog)
{
	ui->setupUi(this);
	setWindowTitle(" ");
}

QPair<QString, QSet<int>> ModifyDialog::modify(const QMap<QString, int>& listToId,
	QWidget* parent, const QPair<QString, QSet<int>>& oldData)
{
	QPair<QString, QSet<int>> retval;
	ModifyDialog w(parent);
	w.ui->title->setText(oldData.first);
	if (oldData.first.isEmpty())
		w.ui->buttonBos->button(QDialogButtonBox::Ok)->setEnabled(false);
	auto list = w.setupBoxList(listToId, oldData.second);
	if (w.exec() == QDialog::Accepted) {
		retval.first = w.ui->title->text();
		for (const auto& i : list)
			if (i->isChecked())
				retval.second.insert(listToId.find(i->text()).value());
	}
	return retval;
}

ModifyDialog::~ModifyDialog() { delete ui; }

QList<QCheckBox*> ModifyDialog::setupBoxList(
	const QMap<QString, int>& listToId, const QSet<int>& activeId)
{
	QList<QCheckBox*> retval;
	auto layout = new QVBoxLayout(ui->list);
	for (auto i = listToId.cbegin(); i != listToId.cend(); ++i) {
		auto check = new QCheckBox(tr("%1-%2").arg(i.value()).arg(i.key()));
		check->setChecked(activeId.contains(i.value()));
		layout->addWidget(check);
		retval.append(check);
	}
	return retval;
}

void ModifyDialog::on_title_editingFinished()
{
	ui->buttonBos->button(QDialogButtonBox::Ok)
		->setEnabled(!ui->title->text().isEmpty());
}
