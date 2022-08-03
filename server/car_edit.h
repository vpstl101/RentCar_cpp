#ifndef CAR_EDIT_H
#define CAR_EDIT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class car_edit;
}

class car_edit : public QDialog
{
    Q_OBJECT

public:
    explicit car_edit(QWidget *parent = nullptr);
    explicit car_edit(std::vector<std::string> data, QWidget *parent = nullptr);
    ~car_edit();

private slots:
    void on_add_btn_clicked();

    void on_edit_btn_clicked();

private:
    Ui::car_edit *ui;
    std::string query;
    std::vector <std::string> datalist;
    QSqlQuery sql;
};

#endif // CAR_EDIT_H
