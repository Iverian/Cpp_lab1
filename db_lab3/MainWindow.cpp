#include "MainWindow.h"
#include "Competition.h"
#include "ModifyDialog.h"
#include "ShowDialog.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QMenu>
#include <QSqlQuery>
#include <initializer_list>
#include <iterator>

using namespace std;

template <class T>
T getFirstQueryVal(const QString& text,
	const QSqlDatabase& db = QSqlDatabase::database(), bool* const status = nullptr);

template <class T>
QSet<T> getSetQueryVals(const QString& text,
	const QSqlDatabase& db = QSqlDatabase::database(), bool* const status = nullptr);

void popupMenu(const QPoint& pos, QWidget* viewport,
	const initializer_list<QAction*>& actList, QWidget* const parent = 0);

void popupMenu(const QPoint& pos, QWidget* viewport,
	const initializer_list<QMenu*>& actList, QWidget* const parent = 0);

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(" ");
}

void MainWindow::on_showMemberList_triggered()
{
	showQuery("SELECT Name FROM Members;");
}

void MainWindow::on_showChoirRating_triggered()
{
	auto choir = Useless::get(toList(getChoirs()), this);
	if (!choir.isEmpty()) {
		auto isCorrect = getFirstQueryVal<bool>(
			tr("SELECT COUNT(*)<>0 FROM Choirs WHERE Name='%1'").arg(choir));
		if (!isCorrect)
			emit error(tr("Unexpected choir name: %1").arg(choir));
		else
			showQuery(tr("WITH Choir_Id AS (SELECT Id FROM Choirs WHERE Name = '%1')"
						 "SELECT '%1' AS Choir, Rating FROM Competitions WHERE Id_choir "
						 "IN (SELECT Id FROM Choir_Id);")
						  .arg(choir));
	}
}

void MainWindow::on_showChoirMembers_triggered()
{
	auto choir = Useless::get(toList(getChoirs()), this);
	if (!choir.isEmpty()) {
		auto isCorrect = getFirstQueryVal<bool>(
			tr("SELECT COUNT(*)<>0 FROM Choirs WHERE Name='%1'").arg(choir));
		if (!isCorrect)
			emit error(tr("Unexpected choir name: %1").arg(choir));
		else
			showQuery(
				tr("WITH Member_Id AS (SELECT Id_Member AS Id FROM Choir_members WHERE "
				   "Id_choir IN (SELECT id FROM Choirs WHERE Name = '%1'))"
				   "SELECT Name FROM Members WHERE Id IN (SELECT Id FROM Member_Id);")
					.arg(choir));
	}
}

void MainWindow::on_showChoirs_triggered() { showQuery("SELECT Name FROM Choirs;"); }

void MainWindow::on_showTopMember_triggered()
{
	showQuery("with member_rating as(select x.id_member, y.rating from choir_members as "
			  "x, competitions as y where x.id_choir=y.id_choir ), member_max as ( "
			  "select id_member from member_rating group by id_member having "
			  "sum(rating) >= all(select sum(rating) from member_rating group by "
			  "id_member) )select name from members where id in (select id_member from "
			  "member_max);");
}

void MainWindow::on_showTopChoir_triggered()
{
	showQuery("with choirrate as (select x.name, y.rating from choirs as x, "
			  "competitions as y where (x.id=y.id_choir)) select name, rating from "
			  "choirrate where (rating in (select max(rating) from choirrate));");
}

void MainWindow::on_showMemberRating_triggered()
{
	showQuery("with member_rating as(select x.id_member, y.rating from choir_members as "
			  "x, competitions as y where x.id_choir=y.id_choir),member_sum as (select "
			  "id_member, sum(rating) as s from member_rating group by id_member order "
			  "by id_member asc) select x.name, y.s from member_sum as y, members as x "
			  "where x.id=y.id_member order by y.s desc;");
}

void MainWindow::on_showLoserChoir_triggered()
{
	showQuery("with choirrate as (select x.name, y.rating from choirs as x, "
			  "competitions as y where (x.id=y.id_choir)) select name, rating from "
			  "choirrate where (rating in (select min(rating) from choirrate));");
}

void MainWindow::on_showLoserMember_triggered()
{
	showQuery("with member_rating as(select x.id_member, y.rating from choir_members as "
			  "x, competitions as y where x.id_choir=y.id_choir ), member_min as ( "
			  "select id_member from member_rating group by id_member having "
			  "sum(rating) <= all(select sum(rating) from member_rating group by "
			  "id_member) )select name from members where id in (select id_member from "
			  "member_min);");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_showBut_customContextMenuRequested(const QPoint& pos)
{
	popupMenu(pos, ui->showBut,
		{ui->showMemberList, ui->showChoirMembers, ui->showChoirs, ui->showTopMember,
			ui->showTopChoir, ui->showLoserMember, ui->showLoserChoir,
			ui->showMemberRating, ui->showChoirRating},
		this);
}

void MainWindow::on_addBut_customContextMenuRequested(const QPoint& pos)
{
	popupMenu(pos, ui->addBut, {ui->addMember, ui->addChoir}, this);
}

void MainWindow::on_delBut_customContextMenuRequested(const QPoint& pos)
{
	auto member = createMenu(getMembers(), SLOT(deleteMember()), this);
	member->setTitle("Members");
	auto choir = createMenu(getChoirs(), SLOT(deleteChoir()), this);
	choir->setTitle("Choirs");
	popupMenu(pos, ui->delBut, {member, choir}, this);
}

void MainWindow::on_editBut_customContextMenuRequested(const QPoint& pos)
{
	auto member = createMenu(getMembers(), SLOT(editMember()), this);
	member->setTitle("Members");
	auto choir = createMenu(getChoirs(), SLOT(editChoir()), this);
	choir->setTitle("Choirs");
	popupMenu(pos, ui->editBut, {member, choir}, this);
}

void popupMenu(const QPoint& pos, QWidget* viewport,
	const initializer_list<QAction*>& actList, QWidget* const parent)
{
	auto menu = new QMenu(parent);
	for (auto& i : actList)
		menu->addAction(i);
	menu->popup(viewport->mapToGlobal(pos));
}

void popupMenu(const QPoint& pos, QWidget* viewport,
	const initializer_list<QMenu*>& actList, QWidget* const parent)
{
	auto menu = new QMenu(parent);
	for (auto& i : actList)
		menu->addMenu(i);
	menu->popup(viewport->mapToGlobal(pos));
}

void MainWindow::on_addMember_triggered()
{
	auto choirs = toMap(getChoirs());
	auto newData = ModifyDialog::modify(choirs, this);
	if (!newData.first.isEmpty()) {
		db().exec(tr("INSERT INTO Members(Name) VALUES ('%1');").arg(newData.first));
		auto newId = getFirstQueryVal<int>("SELECT MAX(Id) FROM Members");
		if (!newData.second.isEmpty()) {
			QString insertStr = "INSERT INTO Choir_members(Id_member,Id_choir) VALUES ";
			for (auto i = newData.second.cbegin(); i != newData.second.cend(); ++i)
				insertStr += tr("(%1,%2)%3")
								 .arg(newId)
								 .arg(*i)
								 .arg(next(i) == newData.second.cend() ? ";" : ",");
			db().exec(insertStr);
		}
	}
}

void MainWindow::on_addChoir_triggered()
{
	auto members = toMap(getMembers());
	auto newData = ModifyDialog::modify(members, this);

	if (!newData.first.isEmpty()) {
		auto rating = Useless::num(-1, this);
		db().exec(tr("INSERT INTO Choirs(Name) VALUES ('%1');").arg(newData.first));
		auto newId = getFirstQueryVal<int>("SELECT MAX(Id) FROM Choirs");
		if (!newData.second.isEmpty()) {
			QString insertStr = "INSERT INTO Choir_members(Id_choir,Id_member) VALUES ";
			for (auto i = newData.second.cbegin(); i != newData.second.cend(); ++i)
				insertStr += tr("(%1,%2)%3")
								 .arg(newId)
								 .arg(*i)
								 .arg(next(i) == newData.second.cend() ? ";" : ",");
			db().exec(insertStr);
		}
		if (rating != -1)
			db().exec(tr("INSERT INTO Competitions(Id_choir,Rating) VALUES (%1,%2);")
						  .arg(newId)
						  .arg(rating));
	}
}

int MainWindow::getId(const QString& text)
{
	QRegExp rx("(\\d+)-.*");
	auto retval = 0;
	if (rx.indexIn(text) != -1)
		retval = rx.cap(1).toInt();
	return retval;
}

QMenu* MainWindow::createMenu(
	const QList<QPair<int, QString>>& list, const char* memberSlot, QWidget* parent)
{
	auto retval = new QMenu(parent);
	for (const auto& i : list)
		retval->addAction(tr("%1-%2").arg(i.first).arg(i.second), this, memberSlot);
	return retval;
}

QStringList MainWindow::toList(const QList<QPair<int, QString>>& list)
{
	QStringList retval;
	for (const auto& i : list)
		retval.append(i.second);
	return retval;
}

QMap<QString, int> MainWindow::toMap(const QList<QPair<int, QString>>& list)
{
	QMap<QString, int> retval;
	for (const auto& i : list)
		retval.insert(i.second, i.first);
	return retval;
}

void MainWindow::editMember()
{
	auto id = getId(qobject_cast<QAction*>(sender())->text());
	auto name
		= getFirstQueryVal<QString>(tr("SELECT Name FROM Members WHERE Id=%1").arg(id));
	auto choirs = getSetQueryVals<int>(
		tr("SELECT Id_choir FROM Choir_members WHERE Id_member=%1").arg(id));
	auto choirNames = toMap(getChoirs());
	auto newData = ModifyDialog::modify(choirNames, this, qMakePair(name, choirs));
	if (!newData.first.isEmpty()) {
		db().exec(
			tr("UPDATE Members SET Name=%1 WHERE Id=%2").arg(newData.first).arg(id));
		db().exec(tr("DELETE FROM Choir_members WHERE Id_member=%1").arg(id));
		if (!newData.second.isEmpty()) {
			QString insertStr = "INSERT INTO Choir_members(Id_member,Id_choir) VALUES ";
			for (auto i = newData.second.cbegin(); i != newData.second.cend(); ++i)
				insertStr += tr("(%1,%2)%3")
								 .arg(id)
								 .arg(*i)
								 .arg(next(i) == newData.second.cend() ? ";" : ",");
			db().exec(insertStr);
		}
	}
}

void MainWindow::editChoir()
{
	auto id = getId(qobject_cast<QAction*>(sender())->text());
	auto name
		= getFirstQueryVal<QString>(tr("SELECT Name FROM Choirs WHERE Id=%1").arg(id));
	auto members = getSetQueryVals<int>(
		tr("SELECT Id_member FROM Choir_members WHERE Id_choir=%1").arg(id));
	auto rating = getFirstQueryVal<int>(
		tr("SELECT Rating FROM Competitions WHERE Id_choir=%1").arg(id));
	auto memberNames = toMap(getMembers());

	auto newData = ModifyDialog::modify(memberNames, this, qMakePair(name, members));
	if (!newData.first.isEmpty()) {
		rating = Useless::num(rating, this);
		db().exec(
			tr("UPDATE Choirs SET Name=%1 WHERE Id=%2").arg(newData.first).arg(id));
		db().exec(tr("DELETE FROM Choir_members WHERE Id_choir=%1").arg(id));
		if (!newData.second.isEmpty()) {
			QString insertStr = "INSERT INTO Choir_members(Id_choir,Id_member) VALUES ";
			for (auto i = newData.second.cbegin(); i != newData.second.cend(); ++i)
				insertStr += tr("(%1,%2)%3")
								 .arg(id)
								 .arg(*i)
								 .arg(next(i) == newData.second.cend() ? ";" : ",");
			db().exec(insertStr);
		}
		if (rating != -1) {
			db().exec(
				tr("UPDATE Competitions SET Rating=%1 WHERE %2;").arg(rating).arg(id));
		}
	}
}

void MainWindow::deleteMember()
{
	auto id = getId(qobject_cast<QAction*>(sender())->text());
	db().exec(tr("DELETE FROM Choir_members WHERE Id_member=%1").arg(id));
	db().exec(tr("DELETE FROM Members WHERE Id=%1").arg(id));
}

void MainWindow::deleteChoir()
{
	auto id = getId(qobject_cast<QAction*>(sender())->text());
	db().exec(tr("DELETE FROM Choir_members WHERE Id_choir=%1").arg(id));
	db().exec(tr("DELETE FROM Competitions WHERE Id_choir=%1").arg(id));
	db().exec(tr("DELETE FROM Choirs WHERE Id=%1").arg(id));
}

void MainWindow::showQuery(const QString& text)
{
	ShowDialog::showQuery(db().exec(text));
}

QList<QPair<int, QString>> MainWindow::getMembers()
{
	auto q = db().exec("SELECT Id,Name FROM Members;");
	QList<QPair<int, QString>> retval;
	while (q.next())
		retval.append({q.value(0).toInt(), q.value(1).toString()});
	return retval;
}

QList<QPair<int, QString>> MainWindow::getChoirs()
{
	auto q = db().exec("SELECT Id,Name FROM Choirs;");
	QList<QPair<int, QString>> retval;
	while (q.next())
		retval.append({q.value(0).toInt(), q.value(1).toString()});
	return retval;
}

QSqlDatabase MainWindow::db() { return QSqlDatabase::database(); }

template <class T>
QSet<T> getSetQueryVals(const QString& text, const QSqlDatabase& db, bool* const status)
{
	auto q = db.exec(text);
	auto stat = q.isSelect();
	if (status)
		*status = stat;
	QSet<T> retval;
	while (q.next())
		retval.insert(q.value(0).value<T>());
	return retval;
}

template <class T>
T getFirstQueryVal(const QString& text, const QSqlDatabase& db, bool* const status)
{
	auto q = db.exec(text);
	auto stat = q.isSelect() && q.next() && q.value(0).isValid();
	auto retval = stat ? q.value(0).value<T>() : T();
	if (status)
		*status = stat;
	q.finish();
	return retval;
}

void MainWindow::on_addBut_clicked()
{
	on_addBut_customContextMenuRequested(ui->addBut->pos());
}

void MainWindow::on_editBut_clicked()
{
	on_editBut_customContextMenuRequested(ui->addBut->pos());
}

void MainWindow::on_delBut_clicked()
{
	on_delBut_customContextMenuRequested(ui->addBut->pos());
}

void MainWindow::on_showBut_clicked()
{
	on_showBut_customContextMenuRequested(ui->addBut->pos());
}
