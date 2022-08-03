#ifndef TRIP_H
#define TRIP_H

#include <QDialog>
#include "database.h"
using namespace  std;

namespace Ui {
class trip;
}

class trip : public QDialog
{
    Q_OBJECT

public:
    explicit trip(QWidget *parent = nullptr);
    ~trip();

private slots:
    void on_sear_clicked();

    void on_back_clicked();

private:
    Ui::trip *ui;
    string query;
    QSqlQuery sql;
};

#endif // TRIP_H
