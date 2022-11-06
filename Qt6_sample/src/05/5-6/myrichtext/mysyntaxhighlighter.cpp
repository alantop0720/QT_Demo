#include "mysyntaxhighlighter.h"
#include <QRegularExpression>

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void MySyntaxHighlighter::highlightBlock(const QString &text) // 高亮文本块
{
    QTextCharFormat myFormat;             // 字符格式
    myFormat.setFontWeight(QFont::Bold);
    myFormat.setForeground(Qt::green);
    QString pattern = "\\bchar\\b";       // 要匹配的字符，这里是“char”单词
    QRegularExpression expression(pattern);          // 创建正则表达式

    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext()) { // 使用匹配迭代器来获取高亮字符的位置并设置格式
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), myFormat);
    }
}

