#include "reservation_del.h"
#include "ui_reservation_del.h"

reservation_del::reservation_del(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservation_del)
{
    ui->setupUi(this);
}

reservation_del::~reservation_del()
{
    delete ui;
}
