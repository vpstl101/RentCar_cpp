#ifndef CARSEARCH_H
#define CARSEARCH_H

#include <QDialog>
#include "database.h"

using namespace  std;

namespace Ui {
class carsearch;
}

class carsearch : public QDialog
{
    Q_OBJECT

public:
    explicit carsearch(QWidget *parent = nullptr);
    ~carsearch();

private slots:
    void on_sear_clicked();
    void on_back_clicked();

private:
    Ui::carsearch *ui;
    string query;
    QSqlQuery sql;

};

#endif // CARSEARCH_H
