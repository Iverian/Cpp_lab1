#pragma once

#include "FileEdit.h"
#include "properties.h"
#include "ui_TextEditor.h"

#include <QMainWindow>
#include <QTabWidget>

class TextEditor : public QMainWindow {
	Q_OBJECT
	prop_ baseWindowTitle = "text editor";

public:
	explicit TextEditor(QWidget* parent = Q_NULLPTR);
protected:
	void closeEvent(QCloseEvent *event) final;
private slots:
	void on_act_newFile_triggered();
	void on_act_openFile_triggered();
	void on_act_save_triggered();
	void on_act_saveAs_triggered();
	void on_act_saveAll_triggered();
	void on_act_close_triggered();
	void on_act_closeAll_triggered();
	void on_act_cut_triggered();
	void on_act_copy_triggered();
	void on_act_paste_triggered();
	void on_act_erase_triggered();
	void on_act_selectAll_triggered();
	void on_tabWidget_tabCloseRequested(int index);
	void on_tabWidget_currentChanged(int index);

private:
	bool closeTab(int index);
	bool closeAll();
	void setHighlighter(FileEdit* edit);
	void save(int index);
	void saveAs(int index);

	Ui::TextEditor m_ui;
};
