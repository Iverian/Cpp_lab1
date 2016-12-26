#include "TextEditor.h"
#include "FileEdit.h"
#include "Highlighter.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>

TextEditor::TextEditor(QWidget* parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);
	HighlighterRegister::instance().init(syntaxRulesDir);
	HighlighterRegister::instance().setTheme(
		Theme({{themeId::KEYWORD, Style::make(Qt::darkBlue, QFont::Bold)},
			{themeId::NUM_LITERAL, Style::make(Qt::darkGreen)},
			{themeId::STR_LITERAL, Style::make(Qt::darkRed)},
			{themeId::FUNCTION,
				Style::make(Qt::darkMagenta, QFont::Bold, QFont::StyleItalic)},
			{themeId::COMMENT,
				Style::make(Qt::gray, QFont::Normal, QFont::StyleItalic)}}));
	this->installEventFilter(this);
	on_act_newFile_triggered();
}

void TextEditor::closeEvent(QCloseEvent* event)
{
	if (!closeAll())
		event->ignore();
	else
		event->accept();
}

void TextEditor::on_act_newFile_triggered()
{
	auto textEdit = new FileEdit;
	m_ui.tabWidget->setCurrentIndex(
		m_ui.tabWidget->addTab(textEdit, QIcon(fileIconPath), QString("untitled")
				+ ((FileEdit::untitledCount() == 1)
						  ? ""
						  : ("-" + QString::number(FileEdit::untitledCount() - 1)))));
}

void TextEditor::on_act_openFile_triggered()
{
	auto absFilename = QFileDialog::getOpenFileName(this);
	if (!absFilename.isEmpty()) {
		QRegExp rx(absolutePathRegex);
		if (rx.indexIn(absFilename) != -1) {
			auto textEdit = new FileEdit(rx.cap(2), rx.cap(1));
			setHighlighter(textEdit);
			m_ui.tabWidget->setCurrentIndex(m_ui.tabWidget->addTab(
				textEdit, QIcon(fileIconPath), textEdit->filename()));
		}
	}
}

void TextEditor::save(int index)
{
	auto currentTab = toFileEdit(m_ui.tabWidget->widget(index));
	if (currentTab->filename().isEmpty())
		on_act_saveAs_triggered();
	else
		currentTab->save();
}

void TextEditor::saveAs(int index)
{
	auto currentTab = toFileEdit(m_ui.tabWidget->widget(index));
	auto absFilename = QFileDialog::getSaveFileName(this);
	if (!absFilename.isEmpty()) {
		QRegExp rx(absolutePathRegex);
		if (rx.indexIn(absFilename) != -1) {
			currentTab->setPath(rx.cap(1));
			currentTab->setFilename(rx.cap(2));
			setHighlighter(currentTab);
			currentTab->save();
			m_ui.tabWidget->setTabText(index, currentTab->filename());
			on_tabWidget_currentChanged(index);
		}
	}
}

void TextEditor::on_act_save_triggered() { save(m_ui.tabWidget->currentIndex()); }

void TextEditor::on_act_saveAs_triggered() { saveAs(m_ui.tabWidget->currentIndex()); }

void TextEditor::on_act_saveAll_triggered()
{
	for (auto i = m_ui.tabWidget->count() - 1; i != -1; --i)
		save(i);
}

void TextEditor::on_act_close_triggered() { closeTab(m_ui.tabWidget->currentIndex()); }

void TextEditor::on_act_closeAll_triggered() { closeAll(); }

void TextEditor::on_act_cut_triggered()
{
	toFileEdit(m_ui.tabWidget->currentWidget())->cut();
}

void TextEditor::on_act_copy_triggered()
{
	toFileEdit(m_ui.tabWidget->currentWidget())->copy();
}

void TextEditor::on_act_paste_triggered()
{
	toFileEdit(m_ui.tabWidget->currentWidget())->paste();
}

void TextEditor::on_act_erase_triggered()
{
	auto tab = toFileEdit(m_ui.tabWidget->currentWidget());
	auto tabCursor = tab->textCursor();
	tabCursor.removeSelectedText();
	tab->setTextCursor(tabCursor);
}

void TextEditor::on_act_selectAll_triggered()
{
	toFileEdit(m_ui.tabWidget->currentWidget())->selectAll();
}

void TextEditor::on_tabWidget_tabCloseRequested(int index) { closeTab(index); }

void TextEditor::on_tabWidget_currentChanged(int index)
{
	setWindowTitle(
		QString("%1: %2").arg(baseWindowTitle, m_ui.tabWidget->tabText(index)));
}

bool TextEditor::closeTab(int index)
{
	auto tab = toFileEdit(m_ui.tabWidget->widget(index));
	auto result = QMessageBox::Discard;
	auto& name = tab->filename();

	if (tab->changed()) {
		QMessageBox saveChanges(QMessageBox::Warning, tr("Save changes?"),
			tr("%1 has been modified, save changes?")
				.arg(name.isEmpty() ? tr("New file") : name),
			, QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, this);
		saveChanges.setDefaultButton(QMessageBox::Save);
		result = saveChanges.exec();
	} else if (index == 0 && name.isEmpty())
		result = QMessageBox::Reset;

	switch (result) {
	case QMessageBox::Save:
		save(index);
	case QMessageBox::Discard:
		m_ui.tabWidget->removeTab(index);
		delete tab;
		if (m_ui.tabWidget->currentIndex() == -1)
			on_act_newFile_triggered();
		break;
	default:
		break;
	}
	return result != QMessageBox::Cancel;
}

bool TextEditor::closeAll()
{
	auto result = true;
	for (auto i = m_ui.tabWidget->count() - 1; i != -1; --i)
		result = closeTab(i) ? result : false;
	return result;
}

void TextEditor::setHighlighter(FileEdit* edit)
{
	HighlighterRegister::instance().setHighlighter(edit->filename(), edit->document());
}
