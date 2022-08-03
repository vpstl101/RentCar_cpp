#ifndef CHATTING_H
#define CHATTING_H
#include <QTcpSocket>
#include <QDialog>
#include "thread.h"
#include "database.h"

namespace Ui {
class chatting;
}

class chatting : public QDialog
{
    Q_OBJECT

public:
    explicit chatting(QTcpSocket * socket, QWidget *parent = nullptr);
    ~chatting();


private slots:
    void show(QString msg);
    void alarm(QString message);
    void on_send_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::chatting *ui;
    QTcpSocket * clntsocket;
    Thread *thread;
    QSqlQuery sql;
    std::string query;
};

#endif // CHATTING_H
