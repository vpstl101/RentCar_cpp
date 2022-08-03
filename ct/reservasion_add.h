#ifndef RESERVASION_ADD_H
#define RESERVASION_ADD_H

#include <QDialog>
#include "database.h"
using namespace std;

namespace Ui {
class reservasion_add;
}

class reservasion_add : public QDialog
{
    Q_OBJECT

public:
    explicit reservasion_add(QString logID, QWidget *parent = nullptr);
    ~reservasion_add();
    void list();

    void show_time();
private slots:
    void on_comboBox_currentIndexChanged();
    void on_booking_clicked();

    void on_back_clicked();

private:
    Ui::reservasion_add *ui;
    string grade;
    string query;
    QSqlQuery sql;
    QString log_id;
    QSqlRecord record;

};

#endif // RESERVASION_ADD_H
