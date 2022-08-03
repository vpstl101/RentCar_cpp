#ifndef RESERV_EDIT_H
#define RESERV_EDIT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class reserv_edit;
}

class reserv_edit : public QDialog
{
    Q_OBJECT

public:
    explicit reserv_edit(std::vector <std::string> data, QWidget *parent = nullptr);
    ~reserv_edit();
    void list();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_edit_button_clicked();

    void on_res_date_dateChanged(const QDate &date);

    void on_ret_date_dateChanged(const QDate &date);

private:
    Ui::reserv_edit *ui;
    std::string query;
    QSqlQuery sql;
    QSqlRecord record;
    std::string reserv_car;
};

#endif // RESERV_EDIT_H
