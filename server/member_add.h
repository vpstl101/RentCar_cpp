#ifndef MEMBER_ADD_H
#define MEMBER_ADD_H

#include <QDialog>
#include "database.h"

namespace Ui {
class member_add;
}

class member_add : public QDialog
{
    Q_OBJECT

public:
    explicit member_add(QWidget *parent = nullptr);
    ~member_add();

private slots:
    void on_add_btn_clicked();

    void on_common_btn_clicked();

    void on_premium_btn_clicked();

    void on_vip_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::member_add *ui;
    std::string grade;
    std::string query;
    QSqlQuery sql;
};

#endif // MEMBER_ADD_H
