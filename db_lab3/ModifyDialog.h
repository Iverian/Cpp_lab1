#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QSet>
#include <QMap>
#include <tuple>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QDialog {
	Q_OBJECT

public:
	static QPair<QString, QSet<int>> modify(const QMap<QString, int>& listToId,
		QWidget* parent = 0,
		const QPair<QString, QSet<int>>& oldData = QPair<QString, QSet<int>>());
	~ModifyDialog();

private slots:
	void on_title_editingFinished();

private:
	QList<QCheckBox*> setupBoxList(
		const QMap<QString, int>& listToId, const QSet<int>& activeId);
	explicit ModifyDialog(QWidget* parent = 0);
	Ui::ModifyDialog* ui;
};

#endif // MODIFYDIALOG_H
