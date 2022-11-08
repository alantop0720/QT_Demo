#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QTest>

//cmd
//on_pushButton_clear_clicked();

//QAbstractItemModel *Imodel=ui->tableView->model();

//QModelIndex Iindex = Imodel->index(index.row(),2);//index.row()为算选择的行号。1为所选中行的第一列。。

//QVariant datatemp=Imodel->data(Iindex);
//QString cmd=datatemp.toString();//name即为所选择行的第一列的值。。。
//qDebug() << cmd;





//QDetachableProcess process;
//QString program = "cmd.exe";
//QStringList arguments = QStringList() << "/K" << cmd;
//process.setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args)
//{
//    args->flags |= CREATE_NEW_CONSOLE;
//    args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;
//});
//process.start(program, arguments);
//process.detach();



//class QDetachableProcess
//        : public QProcess {
//public:
//    QDetachableProcess(QObject *parent = 0)
//        : QProcess(parent) {
//    }
//    void detach() {
//       waitForStarted();
//       setProcessState(QProcess::NotRunning);
//    }
//};



bool boot(QString app, int delay_time, int type)
{
    QFileInfo fileInfo(app);
    if(!fileInfo.isFile())
      {
        qDebug() << ("file is not exist.") << Qt::endl;
        return false;
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


    return true;
}

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);

    // 创建数据库连接
    if (!createConnection()) return 1;

    // 使用QSqlQuery查询连接1的整张表，先要使用连接名获取该连接
    QSqlDatabase db1 = QSqlDatabase::database("connection1");
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from boot");
    while(query1.next())
    {
        qDebug() << query1.value(0).toInt() << query1.value(1).toString() << query1.value(2).toInt() << query1.value(3).toInt() ;

        boot(query1.value(1).toString() , query1.value(2).toInt() , query1.value(3).toInt());
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
    //return a.exec();
}

