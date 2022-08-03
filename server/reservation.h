#ifndef RESERVATION_H
#define RESERVATION_H
#include "database.h"

#include <QDialog>

namespace Ui {
class reservation;
}

class reservation : public QDialog
{
    Q_OBJECT

public:
    explicit reservation(QWidget *parent = nullptr);
    ~reservation();
    void list();

private slots:
    void on_add_btn_clicked();

    void on_edit_btn_clicked();

    void on_delete_btn_clicked();

    void on_pay_clicked();

private:
    Ui::reservation *ui;
    std::string query;
    std::string query2;
    QSqlQuery sql;
    QSqlRecord record;
};

#endif // RESERVATION_H
