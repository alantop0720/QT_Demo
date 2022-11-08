#include "connection.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QSqlDatabase>
#include <QStringList>
#include <QTest>
#include <QVariant>

#include <QThread>

#include <QFileDialog>
#include <QMessageBox>
#include <QString>

#include <QDateTime>

#include <QColor>
#include <QPalette>

#include <QFileInfo>
#include <QProcess>

#include <windows.h>

#include <QDesktopServices>

#include <QSettings>

#include <QAction>
#include <QTextBlock>

#include <QMessageBox>
#include <QPalette>
#include <QThread>
#include <QTime>

// cmd

// QDetachableProcess process;
// QString program = "cmd.exe";
// QStringList arguments = QStringList() << "/K" << cmd;
// process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments
// *args)
//{
//     args->flags |= CREATE_NEW_CONSOLE;
//     args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;
// });
// process.start(program, arguments);
// process.detach();

class QDetachableProcess : public QProcess {
public:
  QDetachableProcess(QObject *parent = 0) : QProcess(parent) {}
  void detach() {
    waitForStarted();
    setProcessState(QProcess::NotRunning);
  }
};

void boot(QString app, int delay_time, int type) {
  if (type == 1) {
    QDetachableProcess process;
    QString program = "cmd.exe";
    QStringList arguments = QStringList() << "/K" << app;
    process.setCreateProcessArgumentsModifier(
        [](QProcess::CreateProcessArguments *args) {
          args->flags |= CREATE_NEW_CONSOLE;
          args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
        });
    process.start(program, arguments);
    process.detach();
    QTest::qSleep(1000 * delay_time);

  }

  if (type == 2) {
    QFileInfo fileInfo(app);
    if (!fileInfo.isFile()) {
      qDebug() << ("file is not exist.") << Qt::endl;
    }

      QProcess *myProcess = new QProcess();

      QFileInfo fileinfo = QFileInfo(app);

      QString filepath = fileinfo.absolutePath();

      qDebug() << QDir::currentPath();

      qDebug() << "filepath = " << filepath;

      QString oldCurrent = QDir::currentPath();
      QDir::setCurrent(filepath);

      qDebug() << "oldCurrent=" << oldCurrent;

      qDebug() << QDir::currentPath();

      QString cmd = "\"" + app + "\"";
      qDebug() << cmd;

      myProcess->startDetached(cmd);

      qDebug() << "setCurrent=" << QDir::setCurrent(oldCurrent);

      QTest::qSleep(1000 * delay_time);



  }
}

  int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);

    // 创建数据库连接
    if (!createConnection())
      return 1;

    // 使用QSqlQuery查询连接1的整张表，先要使用连接名获取该连接
    QSqlDatabase db1 = QSqlDatabase::database("connection1");
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from boot");
    while (query1.next()) {
      qDebug() << query1.value(0).toInt() << query1.value(1).toString()
               << query1.value(2).toInt() << query1.value(3).toInt();

      boot(query1.value(1).toString(), query1.value(2).toInt(),
           query1.value(3).toInt());
    }

    //    // 使用QSqlQuery查询连接2的整张表
    //    QSqlDatabase db2 = QSqlDatabase::database("connection2");
    //    QSqlQuery query2(db2);
    //    qDebug() << "connection2:";
    //    query2.exec("select * from student");
    //    while(query2.next())
    //    {
    //        qDebug() << query2.value(0).toInt() << query2.value(1).toString();
    //    }
    // return a.exec();
  }
