#include "regexpplugin.h"
#include <QRegularExpression>
#include <QtPlugin>

QString RegExpPlugin::regexp(const QString &message)
{
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(message);
    if(match.hasMatch()) {
        QString str = match.captured(0);
        return str;
    } else return 0;
}

