#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QTcpSocket>
#include <QRegExp>
#include <thread>
#include "database.h"
#include "mainwindow.h"
using namespace std;

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QString log_id, QWidget *parent = nullptr);
    ~chat();
private slots:
    void readyRead();
    void connected();
    void on_send_clicked();

private:
    Ui::chat *ui;
    QTcpSocket* socket;
    string query;
    QSqlQuery sql;
    QString logid;
    QSqlRecord record;
};

#endif // CHAT_H
