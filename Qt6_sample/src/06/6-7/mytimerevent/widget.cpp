#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include <QPalette>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    id1 = startTimer(1000);                  // 开启一个1秒定时器，返回其ID
    id2 = startTimer(1500);
    id3 = startTimer(2200);

    QTimer *timer = new QTimer(this);           // 创建一个新的定时器
    // 关联定时器的溢出信号到槽上
    connect(timer, &QTimer::timeout, this, &Widget::timerUpdate);
    timer->start(1000);                         // 设置溢出时间为1秒，并启动定时器


    QTimer::singleShot(20000, this, &Widget::close);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1) {       // 判断是哪个定时器
        qDebug() << "timer1";
    }
    else if (event->timerId() == id2) {
        qDebug() << "timer2";
    }
    else {
        qDebug() << "timer3";
    }
}

void Widget::timerUpdate()                  // 定时器溢出处理
{
    QTime time = QTime::currentTime();      // 获取当前时间
    QString text = time.toString("hh:mm");  // 转换为字符串
    if((time.second() % 2) == 0) text[2]=' '; // 每隔一秒就将“：”显示为空格
    ui->lcdNumber->display(text);

    int rand1 = QRandomGenerator::global()->bounded(256);  // 产生0-255范围内的随机数
    int rand2 = QRandomGenerator::global()->bounded(256);
    int rand3 = QRandomGenerator::global()->bounded(256);
    qDebug() << "rand: " << rand1 << rand2 << rand3;
    QColor color(rand1, rand2, rand3);
    //获取部件的调色板，通过调色板设置显示数字的颜色
    QPalette palette = ui->lcdNumber->palette();
    palette.setColor(QPalette::WindowText, color);
    ui->lcdNumber->setPalette(palette);

}

