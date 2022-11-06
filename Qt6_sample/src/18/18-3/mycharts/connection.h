#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

    // 创建course表
    query.exec("create table m_xy (id int primary key, "
                       "m_x int, m_y int)");
    query.exec("insert into m_xy values(0, 2, 3)");
    query.exec("insert into m_xy values(1, 5, 8)");
    query.exec("insert into m_xy values(2, 7, 4)");
    query.exec("insert into m_xy values(3, 9, 5)");

    return true;
}

#endif // CONNECTION_H

