#ifndef RESERVASION_EDIT_H
#define RESERVASION_EDIT_H

#include <QDialog>
#include "database.h"
using namespace  std;

namespace Ui {
class reservasion_edit;
}

class reservasion_edit : public QDialog
{
    Q_OBJECT

public:
    explicit reservasion_edit(QString logid, QWidget *parent = nullptr);
    ~reservasion_edit();

    void reserList();
    void carList();

private slots:
    void on_reser_clicked();
    void on_back_clicked();



    void on_car_list_cellDoubleClicked();

    void on_reser_date_dateChanged();

    void on_return_date_dateChanged();

private:
    Ui::reservasion_edit *ui;
    string query;
    QSqlQuery sql;
    QString log_id;
    QSqlRecord record;
    QString reserv_car;
};

#endif // RESERVASION_EDIT_H
