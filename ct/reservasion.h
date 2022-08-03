#ifndef RESERVASION_H
#define RESERVASION_H

#include <QDialog>
#include "database.h"
#include "reservasion_edit.h"
#include "pay.h"
#include "reservasion_add.h"
using namespace  std;

namespace Ui {
class reservasion;
}

class reservasion : public QDialog
{
    Q_OBJECT

public:
    explicit reservasion(QString logid, QWidget *parent = nullptr);
    ~reservasion();
    void reserlist();

private slots:
    void on_reser_clicked();

    void on_del_clicked();

    void on_pay_clicked();

    void on_back_clicked();

    void on_real_reser_clicked();

private:
    Ui::reservasion *ui;
    string query;
    QSqlQuery sql;
    QString log_id;
    QSqlRecord record;

};

#endif // RESERVASION_H
