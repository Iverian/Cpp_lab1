#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();
signals:
	void error(QString);
private slots:
	void on_showBut_customContextMenuRequested(const QPoint& pos);
	void on_addBut_customContextMenuRequested(const QPoint& pos);
	void on_delBut_customContextMenuRequested(const QPoint& pos);
	void on_editBut_customContextMenuRequested(const QPoint& pos);

	void on_addChoir_triggered();
	void on_addMember_triggered();

	void on_showMemberList_triggered();
	void on_showChoirRating_triggered();
	void on_showChoirMembers_triggered();
	void on_showChoirs_triggered();
	void on_showTopMember_triggered();
	void on_showTopChoir_triggered();
	void on_showMemberRating_triggered();
	void on_showLoserChoir_triggered();
	void on_showLoserMember_triggered();

	int getId(const QString& text);
	void editMember();
	void editChoir();
	void deleteMember();
	void deleteChoir();

	void showQuery(const QString& text);
private:
	QSqlDatabase db();
	QMenu* createMenu(const QList<QPair<int, QString>>& list, const char* memberSlot,
		QWidget* parent = 0);
	QStringList toList(const QList<QPair<int, QString>>& list);
	QMap<QString, int> toMap(const QList<QPair<int, QString>>& list);
	QList<QPair<int, QString>> getMembers();
	QList<QPair<int, QString>> getChoirs();

	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
