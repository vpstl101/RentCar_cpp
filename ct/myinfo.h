#ifndef MYINFO_H
#define MYINFO_H

#include <QDialog>
#include "database.h"
#include "menu.h"
#include "withdraw.h"

using namespace  std;

namespace Ui {
class myinfo;
}

class myinfo : public QDialog
{
    Q_OBJECT

public:
    explicit myinfo(QString log_id, QWidget *parent = nullptr);
    ~myinfo();
    void list();

private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_back_clicked();
    void on_out_clicked();
    void on_modify_clicked();

private:
    Ui::myinfo *ui;
    string choose;
    string query;
    QSqlQuery sql;
    QString logid;
    QSqlRecord record;

};

#endif // MYINFO_H
