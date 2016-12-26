#pragma once

#include <QColor>
#include <QFont>
#include <QMap>
#include <QPair>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>
#include <initializer_list>

enum class ruleId : int {
	KEYWORD,
	STR_LITERAL,
	NUM_LITERAL,
	FUNCTION,
	SINGLE_LINE_COMMENT,
	MULTI_LINE_COMMENT_BEGIN,
	MULTI_LINE_COMMENT_END,
	END
};

ruleId& operator++(ruleId& x);

enum class themeId : int { KEYWORD, STR_LITERAL, NUM_LITERAL, FUNCTION, COMMENT, END };

bool isSegmentsSuperimpose(QPair<int, int> lhs, QPair<int, int> rhs);

struct Style {
	static Style make(Qt::GlobalColor color = Qt::black, QFont::Weight fontWeight = QFont::Normal,
		QFont::Style fontStyle = QFont::StyleNormal);

	Style(const QColor& color = QColor(Qt::black), QFont::Weight fontWeight = QFont::Normal,
		QFont::Style fontStyle = QFont::StyleNormal);
	QTextCharFormat format() const;

private:
	QColor m_color;
	QFont::Weight m_fontWeight;
	QFont::Style m_fontStyle;
};

struct Theme {
	using pair_t = QPair<themeId, Style>;

	Theme();
	Theme(const std::initializer_list<pair_t>& list);
	const Style& at(ruleId rule) const;
	const Style& at(themeId theme) const;
	static themeId toTheme(ruleId id);

private:
	QVector<Style> m_theme;
};

struct DocumentHighlighter;

struct Highlighter {
	Highlighter();
	QRegExp ruleRegex(ruleId id) const;
	const QString& rule(ruleId id) const;
	Highlighter& setRule(ruleId id, const QString& value);
	DocumentHighlighter* highlight(QTextDocument* document) const;

private:
	QVector<QString> m_rules;
};

struct HighlighterRegister {
	static HighlighterRegister& instance();

	const Highlighter& at(const QString& index) const;
	HighlighterRegister& insert(const QString& index, Highlighter* value);
	const Theme& theme() const;
	HighlighterRegister& setTheme(const Theme& theme);
	HighlighterRegister& init(const QString& path);
	DocumentHighlighter* setHighlighter(const QString& filename, QTextDocument* doc) const;

private:
	HighlighterRegister();
	void fetchFile(const QString& filename);

	QMap<QString, Highlighter*> m_map;
	Theme m_theme;
};

class DocumentHighlighter : public QSyntaxHighlighter {
	Q_OBJECT
	friend struct Highlighter;
	enum blockState { NIL = -1, COMMENT = 0 };

protected:
	void highlightBlock(const QString& text) override;

private:
	DocumentHighlighter(QTextDocument* document, const Highlighter& parent);

	const Highlighter& m_parent;
};
