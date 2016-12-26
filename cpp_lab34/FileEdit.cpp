#include "FileEdit.h"
#include "Highlighter.h"
#include "utility.h"

#include <QDebug>
#include <QDir>

static const auto endlByteArray = QByteArray("\n");

int FileEdit::m_untitledCounter(0);

FileEdit::FileEdit(const QString& filename, const QString& path, QWidget* parent)
	: QPlainTextEdit(parent)
	, m_filename()
	, m_path()
	, m_changed(false)
{
	connect(this, SIGNAL(textChanged()), this, SLOT(on_textChanged_triggered()));

	++m_untitledCounter;
	setPath(path);
	setFilename(filename);
	load();
}

FileEdit::~FileEdit()
{
	if (m_filename.isEmpty())
		--m_untitledCounter;
}

void FileEdit::load()
{
	if (!m_filename.isEmpty()) {
		QFile f(path() + "/" + m_filename);
		if (f.open(QIODevice::ReadOnly))
			while (!f.atEnd())
				appendPlainText(QString(f.readLine()));
		m_changed = false;
	}
}

void FileEdit::save()
{
	if (!m_filename.isEmpty()) {
		QFile f(path() + "/" + m_filename);
		if (f.open(QIODevice::WriteOnly)) {
			auto cursor = textCursor();
			cursor.movePosition(QTextCursor::Start);
			do {
				cursor.select(QTextCursor::BlockUnderCursor);
				auto dat = cursor.selectedText();
				if (!dat.isEmpty()) {
					if (dat.at(0) == QChar::ParagraphSeparator)
						dat.replace(0, 1, "\n");
					auto raw = dat.toUtf8();
					f.write(raw.data(), raw.length());
				}
			} while (cursor.movePosition(QTextCursor::NextBlock));
		}
		m_changed = false;
	}
}

FileEdit& FileEdit::setFilename(const QString& filename)
{
	if (!filename.isEmpty()) {
		if (m_filename.isEmpty())
			--m_untitledCounter;
		m_filename = filename;
	}
	return *this;
}

FileEdit& FileEdit::setPath(const QString& path)
{
	m_path = path;
	if (!m_filename.isEmpty()) {
		m_filename.clear();
		++m_untitledCounter;
	}
	return *this;
}

QString FileEdit::path() const
{
	return m_path.isEmpty() ? QDir::currentPath() : m_path;
}

bool FileEdit::changed() const
{
	return m_changed;
}

const QString& FileEdit::filename(void) const
{
	return m_filename;
}

const int& FileEdit::untitledCount(void)
{
	return m_untitledCounter;
}

void FileEdit::on_textChanged_triggered()
{
	m_changed = true;
}
