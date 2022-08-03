#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "carsearch.h"
#include "myinfo.h"
#include "trip.h"
#include "reservasion.h"
#include "reservasion_edit.h"
#include "chat.h"

using namespace  std;

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QString logid, QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_my_info_clicked();
    void on_trip_clicked();
    void on_car_search_clicked();
    void on_reservasion_clicked();
    void on_pay_2_clicked();
    void on_chating_clicked();

private:
    Ui::menu *ui;
    QString log_id;

};

#endif // MENU_H
