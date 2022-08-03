#ifndef MEMBER_EDIT_H
#define MEMBER_EDIT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class member_edit;
}

class member_edit : public QDialog
{
    Q_OBJECT

public:
    explicit member_edit(std::vector<std::string> data, QWidget *parent = nullptr);
    ~member_edit();

private slots:
    void on_edit_btn_clicked();

    void on_common_btn_clicked();

    void on_premium_btn_clicked();

    void on_vip_btn_clicked();

private:
    Ui::member_edit *ui;
    QSqlQuery sql;
    std::string query;
    std::string grade;
};

#endif // MEMBER_EDIT_H
