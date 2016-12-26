#include "Highlighter.h"
#include "properties.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <limits>

Style Style::make(Qt::GlobalColor color, QFont::Weight fontWeight, QFont::Style fontStyle)
{
	return Style(QColor(color), fontWeight, fontStyle);
}

Style::Style(const QColor& color, QFont::Weight fontWeight, QFont::Style fontStyle)
	: m_color(color)
	, m_fontWeight(fontWeight)
	, m_fontStyle(fontStyle)
{
}

QTextCharFormat Style::format() const
{
	QTextCharFormat retval;
	retval.setFontWeight(m_fontWeight);
	if (m_fontStyle == QFont::StyleItalic)
		retval.setFontItalic(true);
	retval.setForeground(m_color);
	return retval;
}

Theme::Theme()
	: m_theme()
{
}

Theme::Theme(const std::initializer_list<Theme::pair_t>& list)
	: m_theme((int)themeId::END)
{
	for (const auto& i : list)
		m_theme[(int)i.first] = i.second;
}

const Style& Theme::at(ruleId rule) const
{
	return m_theme.at((int)toTheme(rule));
}

const Style& Theme::at(themeId theme) const
{
	return m_theme.at((int)theme);
}

themeId Theme::toTheme(ruleId id)
{
	themeId retval;
	switch (id) {
	case ruleId::KEYWORD:
		retval = themeId::KEYWORD;
		break;
	case ruleId::STR_LITERAL:
		retval = themeId::STR_LITERAL;
		break;
	case ruleId::NUM_LITERAL:
		retval = themeId::NUM_LITERAL;
		break;
	case ruleId::FUNCTION:
		retval = themeId::FUNCTION;
		break;
	case ruleId::SINGLE_LINE_COMMENT:
	case ruleId::MULTI_LINE_COMMENT_BEGIN:
	case ruleId::MULTI_LINE_COMMENT_END:
		retval = themeId::COMMENT;
		break;
	case ruleId::END:
	default:
		retval = themeId::END;
		break;
	}
	return retval;
}

HighlighterRegister& HighlighterRegister::instance()
{
	static HighlighterRegister inst;
	return inst;
}

const Highlighter& HighlighterRegister::at(const QString& index) const
{
	return *m_map[index];
}

HighlighterRegister& HighlighterRegister::insert(const QString& index, Highlighter* value)
{
	m_map.insert(index, value);
	return *this;
}

const Theme& HighlighterRegister::theme() const
{
	return m_theme;
}

HighlighterRegister& HighlighterRegister::setTheme(const Theme& theme)
{
	m_theme = theme;
	return *this;
}

DocumentHighlighter* HighlighterRegister::setHighlighter(const QString& filename, QTextDocument* doc) const
{
	DocumentHighlighter* retval = Q_NULLPTR;
	QRegExp filenameExpr(filenameRegex);
	if (filenameExpr.indexIn(filename) != -1)
		if (m_map.contains(filenameExpr.cap(2)))
			retval = at(filenameExpr.cap(2)).highlight(doc);
	return retval;
}

HighlighterRegister::HighlighterRegister()
	: m_map()
	, m_theme()
{
}

HighlighterRegister& HighlighterRegister::init(const QString& path)
{
	QDir dir(path);
	auto list = dir.entryList(QStringList(QString(syntaxFileMask)), QDir::Files);
	for (const auto& i : list)
		fetchFile(path + "/" + i);
	return *this;
}

void HighlighterRegister::fetchFile(const QString& filename)
{
	QFile f(filename);
	if (f.open(QIODevice::ReadOnly)) {
		QTextStream is(&f);
		auto h = new Highlighter;
		auto ext = is.readLine();
		for (auto i = ruleId::KEYWORD; i != ruleId::END && !is.atEnd(); ++i)
			h->setRule(i, is.readLine());
		QTextStream s(&ext);
		for (QString tmp; !s.atEnd();) {
			s >> tmp;
			insert(tmp, h);
		}
	}
}

Highlighter::Highlighter()
	: m_rules((int)ruleId::END)
{
}

QRegExp Highlighter::ruleRegex(ruleId id) const
{
	return QRegExp(m_rules.at((int)id));
}

const QString& Highlighter::rule(ruleId id) const
{
	return m_rules.at((int)id);
}

Highlighter& Highlighter::setRule(ruleId id, const QString& value)
{
	m_rules[(int)id] = value;
	return *this;
}

DocumentHighlighter* Highlighter::highlight(QTextDocument* document) const
{
	return new DocumentHighlighter(document, *this);
}

DocumentHighlighter::DocumentHighlighter(QTextDocument* document, const Highlighter& parent)
	: QSyntaxHighlighter(document)
	, m_parent(parent)
{
}

void DocumentHighlighter::highlightBlock(const QString& text)
{
	auto beginRegex = m_parent.ruleRegex(ruleId::MULTI_LINE_COMMENT_BEGIN);
	auto endRegex = m_parent.ruleRegex(ruleId::MULTI_LINE_COMMENT_END);
	auto commentSegment = qMakePair(beginRegex.indexIn(text), endRegex.indexIn(text));

	if (previousBlockState() == COMMENT)
		commentSegment.first = 0;

	if (commentSegment.first != -1) {
		auto format = HighlighterRegister::instance().theme().at(themeId::COMMENT).format();
		if (commentSegment.second != -1) {
			setFormat(commentSegment.first,
				commentSegment.second + endRegex.matchedLength() - commentSegment.first, format);
		} else {
			setFormat(commentSegment.first, text.length() - commentSegment.first, format);
			setCurrentBlockState(COMMENT);
			commentSegment.second = std::numeric_limits<int>::max();
		}
	} else
		commentSegment = qMakePair(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

	for (auto i = ruleId::KEYWORD; i != ruleId::MULTI_LINE_COMMENT_BEGIN; ++i) {
		auto regex = m_parent.ruleRegex(i);
		auto format = HighlighterRegister::instance().theme().at(i).format();
		auto index = regex.indexIn(text);
		while (index != -1) {
			auto length = regex.matchedLength();
			if (!isSegmentsSuperimpose(commentSegment, qMakePair(index, index + length)))
				setFormat(index, regex.cap(1).length(), format);
			index = regex.indexIn(text, index + length);
		}
	}
}

bool isSegmentsSuperimpose(QPair<int, int> lhs, QPair<int, int> rhs)
{
	return !(lhs.second <= rhs.first || rhs.second <= lhs.first);
}

ruleId& operator++(ruleId& x)
{
	if (x != ruleId::END)
		x = ruleId((int)x + 1);
	return x;
}
