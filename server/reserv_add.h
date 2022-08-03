#ifndef RESERV_ADD_H
#define RESERV_ADD_H
#include "database.h"
#include <QDialog>

namespace Ui {
class reserv_add;
}

class reserv_add : public QDialog
{
    Q_OBJECT

public:
    explicit reserv_add(QWidget *parent = nullptr);
    ~reserv_add();
    void list();
    void show_time();
    void userlist();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_booking_btn_clicked();

    void on_common_btn_clicked();

    void on_premium_btn_clicked();

    void on_vip_btn_clicked();

private:
    Ui::reserv_add *ui;
    std::string query;
    std::string query2;
    QSqlQuery sql;
    QSqlRecord record;
    QSqlRecord record2;
    std::string grade;
};

#endif // RESERV_ADD_H
