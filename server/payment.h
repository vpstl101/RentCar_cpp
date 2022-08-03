#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class payment;
}

class payment : public QDialog
{
    Q_OBJECT

public:
    explicit payment(std::vector <std::string> data, QWidget *parent = nullptr);
    ~payment();
    void text_setting(std::vector <std::string> data);

private slots:

    void on_point_btn_clicked();

    void on_pay_btn_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::payment *ui;
    std::string query;
    QSqlQuery sql;
    QSqlRecord record;
    std::string ID;
    std::string total;
    std::string reserv_num;
    int plus_ins;
    int use_point;
    int totalcharge;
    int sale;
    int insurance;
};

#endif // PAYMENT_H
