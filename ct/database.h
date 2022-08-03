#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <cstring>

class Database
{
private:
    QSqlDatabase db;
public:
    Database() {
        open_db();
    }
    void open_db()
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("10.10.20.40");      // IP 또는 DNS Host name
        db.setPort(3306);
        db.setDatabaseName("rent"); // DB명
        db.setUserName("admin");     // 계정 명
        db.setPassword("1234");     // 계정 Password
        //qDebug()<<QSqlDatabase::drivers();

        if(!db.open())
        {
            qDebug()<<"connect error";
            exit(1);
        }
    }
    ~Database() {
        db.close();
    }
};

#endif // DATABASE_H
