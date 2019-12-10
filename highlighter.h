#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    Highlighter(QTextDocument* parent = 0);

protected:
    void highlightBlock(const QString& text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> rules_;
};

#endif  // HIGHLIGHTER_H
