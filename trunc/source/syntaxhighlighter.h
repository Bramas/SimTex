#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextEdit;

class SyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SyntaxHighlighter(QTextEdit * parent);

protected:
    virtual void highlightBlock(const QString &text);
    void highlightExpression(const QString &text, const QString &pattern, const QTextCharFormat &format);
};

#endif // SYNTAXHIGHLIGHTER_H
