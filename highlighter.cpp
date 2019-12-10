#include "highlighter.h"
#include "token.h"

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;
    QTextCharFormat format;

    // keyword highlight
    format.setForeground(Qt::blue);
    format.setFontWeight(QFont::Bold);
    rule.format = format;
    for (auto i = Token::kNone + 2; i < Token::kKey; ++i) {
        rule.pattern = QRegExp(QString("\\b%1\\b").arg(Token::pattern_[i]));
        rules_.append(rule);
    }

    // command highlight
    format.setForeground(Qt::red);
    rule.format = format;
    rule.pattern = QRegExp(QString("\\bRUN\\b"));
    rules_.append(rule);
    rule.pattern = QRegExp(QString("\\bLIST\\b"));
    rules_.append(rule);
    rule.pattern = QRegExp(QString("\\bCLEAR\\b"));
    rules_.append(rule);
    rule.pattern = QRegExp(QString("\\bHELP\\b"));
    rules_.append(rule);
    rule.pattern = QRegExp(QString("\\bQUIT\\b"));
    rules_.append(rule);

    // comment hightlight
    format.setForeground(Qt::darkGreen);
    format.setFontWeight(QFont::Normal);
    rule.pattern = QRegExp("REM( [^\n]*)?$");
    rule.format = format;
    rules_.append(rule);
}

void Highlighter::highlightBlock(const QString& text) {
    for (auto& i : rules_) {
        QRegExp expression(i.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, i.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
