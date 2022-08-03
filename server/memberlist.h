#ifndef MEMBERLIST_H
#define MEMBERLIST_H
#include "database.h"
#include <QDialog>

namespace Ui {
class memberlist;
}

class memberlist : public QDialog
{
    Q_OBJECT

public:
    explicit memberlist(QWidget *parent = nullptr);
    ~memberlist();

private slots:
    void list(std::string type);

    void on_edit_btn_clicked();

    void on_delete_btn_clicked();

    void on_common_btn_clicked();

    void on_premium_btn_clicked();

    void on_vip_btn_clicked();



    void on_new_btn_clicked();

private:
    Ui::memberlist *ui;
    std::string query;
    std::string grade;
    QSqlQuery sql;
    QSqlRecord record;
};

#endif // MEMBERLIST_H
