#ifndef MEMBERMODIFY_H
#define MEMBERMODIFY_H

#include <QDialog>

namespace Ui {
class MemberModify;
}

class MemberModify : public QDialog
{
	Q_OBJECT

public:
	static void modify(QWidget* parent = 0, int id = -1);
	explicit MemberModify(QWidget *parent = 0, int id = -1);
	~MemberModify();

private:
	int m_id;
	Ui::MemberModify *ui;
};

#endif // MEMBERMODIFY_H
