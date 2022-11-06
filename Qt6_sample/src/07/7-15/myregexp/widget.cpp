#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QRegularExpression>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QRegularExpression re("^\\d\\d?$");     // 两个字符都必须为数字，第二个字符可以没有
    QString str = "a1";
    qDebug() << str.indexOf(re);            // 结果为-1，不是数字开头
    str = "5";
    qDebug() << str.indexOf(re);            // 结果为0
    str = "5b";
    qDebug() << str.indexOf(re);            // 结果为-1，第二个字符不是数字
    str = "12";
    qDebug() << str.indexOf(re);            // 结果为0
    str = "123";
    qDebug() << str.indexOf(re);            // 结果为-1，超过了两个字符
    re.setPattern(R"(^\d\d?$)");            // 使用原始字符串文字，无须对反斜杠进行转义
    str = "33";
    qDebug() << str.indexOf(re);            // 结果为0

    qDebug() << "*******************";      // 输出分割符，为了显示清晰
    re.setPattern("\\b(mail|letter)\\b");   // 匹配mail或者letter单词
    str = "emailletter";
    qDebug() << str.indexOf(re);            // 结果为-1，mail不是一个单词
    str = "my mail";
    qDebug() << str.indexOf(re);            // 返回3
    str = "my email letter";
    qDebug() << str.indexOf(re);            // 返回9
    qDebug() << "*******************";
    re.setPattern("M(?!ail)");              // 匹配字符M，其后面不能跟有ail字符
    str = "this is M";
    str.replace(re, "Mail");                // 使用"Mail"替换匹配到的字符
    qDebug() << "str: " << str;             // 结果为this is Mail
    str = "my M,your Ms,his Mail";
    qDebug() << str.contains(re);           // 结果为true
    qDebug() << str.lastIndexOf(re);        // 结果为10
    str.replace(re,"Mail");
    qDebug() << "str: " << str;             // 结果为my Mail,your Mails,his Mail
    qDebug() << str.contains(re);           // 结果为false
    re.setPatternOptions(QRegularExpression::CaseInsensitiveOption); // 设置不区分大小写
    qDebug() << str.contains(re);           // 结果为true
    qDebug() << "*******************";
    QString str1 = "One Eric another Eirik, and an Ericsson. "
                   "How many Eiriks, Eric?"; // 一个字符串如果一行写不完，换行后两行都需要加双引号
    QRegularExpression re1("\\bEi?ri[ck]\\b"); // 匹配Eric或者Eirik
    // 获取匹配到的数目，方式1：手动循环获取，方便对每一个位置进行操作
    qDebug() << tr("方式1：");
    int pos = 0;
    int count = 0;
    while (pos >= 0) {
        pos = str1.indexOf(re1, pos);
        if (pos >= 0) {
            qDebug()  << "pos: " << pos;
            ++pos;                             // 从匹配的字符的下一个字符开始匹配
            ++count;                           // 匹配到的数目加1
        }
    }
    qDebug() << "count: " << count;            // 结果为3

    // 获取匹配到的数目，方式2：直接使用count()函数获取
    qDebug() << tr("方式2：");
    qDebug() << "count: " << str1.count(re1);

    qDebug() << "*******************";

    // 贪婪的和非贪婪的
    str = "20005";
    re.setPattern("0+");
    qDebug() << "greedy count: " << str.replace(re, "1"); // 结果为215

    str = "20005";
    re.setPattern("0+?");  // 方式1
    //re.setPatternOptions(QRegularExpression::InvertedGreedinessOption); // 方式2
    qDebug() << "lazy count: " << str.replace(re, "1"); // 结果为21115


    qDebug() << "*******7-15********";

    re.setPattern("(mail|letter)(.)");
    QRegularExpressionMatch match = re.match("I Sent you some email!");
    if (match.hasMatch()) {
        QString matched = match.captured(0);
        QString matched1 = match.captured(1);
        QString matched2 = match.captured(2);
        qDebug() << "matched: " << matched << Qt::endl   // 结果为mail!
                 <<"matched1: " << matched1 << Qt::endl  // 结果为mail
                <<"matched2: " << matched2 << Qt::endl; // 结果为!
    }
    // 通过\1使用捕获的字符串
    re.setPattern("\\b(\\w+)\\W+\\1\\b");
    match = re.match("Hello--hello");
    qDebug() << match.hasMatch()    // 结果为true
             << match.captured(0)   // 结果为Hello--hello
             << match.captured(1);  // 结果为Hello

    re.setPattern("abc(\\d+)def");
    match = re.match("XYZabc123defXYZ");
    if (match.hasMatch()) {
        qDebug() << match.captured(1)         // 结果为123
                 << match.capturedStart(1)    // 结果为6
                 << match.capturedEnd(1);     // 结果为9
    }


    re.setPattern("^(?<date>\\d\\d)/(?<month>\\d\\d)/(?<year>\\d\\d\\d\\d)$");
    match = re.match("08/12/1985");
    if (match.hasMatch()) {
        qDebug() << match.captured("date")   // 结果为08
                 <<match.captured("month")   // 结果为12
                 <<match.captured("year");   // 结果为1985
    }


    re.setPattern("\\d\\d \\w+");
    match = re.match("12 abc 45 def", 1);
    qDebug() << match.hasMatch() << match.captured(0); // 结果为：45 def


    re.setPattern(re.anchoredPattern("\\d\\d \\w+"));
    qDebug() <<re.pattern();
    match = re.match("12 abc");
    qDebug() << match.hasMatch() << match.captured(0); // 结果为：12 abc


}

Widget::~Widget()
{
    delete ui;
}






