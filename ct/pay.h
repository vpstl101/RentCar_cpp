#ifndef PAY_H
#define PAY_H

#include <QDialog>
#include "database.h"

using namespace std;

namespace Ui {
class pay;
}

class pay : public QDialog
{
    Q_OBJECT

public:
    explicit pay(QString logID, QWidget *parent = nullptr);
    ~pay();
    void pay_input();
    void point_search();
    void sale_grade();

private slots:
    void on_back_clicked();
    void on_money_pay_clicked();
    void on_card_pay_clicked();

private:
    Ui::pay *ui;
    string query;
    QSqlQuery sql;
    QString logid;
    string choose;
    int point_use;
    int g_total;
    int premium_sale;
    int vip_sale;
};

#endif // PAY_H
