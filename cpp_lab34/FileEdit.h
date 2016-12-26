#pragma once

#include <QPlainTextEdit>

#define toFileEdit(ptr) qobject_cast<FileEdit*>(ptr)

class FileEdit : public QPlainTextEdit {
	Q_OBJECT
public:
	explicit FileEdit(const QString& filename = QString::null, const QString& path = QString::null,
		QWidget* parent = Q_NULLPTR);
	~FileEdit();

	FileEdit& setFilename(const QString& filename = QString::null);
	FileEdit& setPath(const QString& path);
	const QString& filename(void) const;
	QString path() const;
	bool changed() const;

	void save();
	void load();

	static const int& untitledCount();
private slots:
	void on_textChanged_triggered();

private:
	static int m_untitledCounter;
	QString m_filename;
	QString m_path;
	bool m_changed;
};
