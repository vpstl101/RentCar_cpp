#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QDialog>
#include "database.h"

using namespace std;

namespace Ui {
class withdraw;
}

class withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit withdraw(QString logid, QWidget *parent = nullptr);
    ~withdraw();

private slots:
    void on_draw_button_clicked();

private:
    Ui::withdraw *ui;
    string query;
    QSqlQuery sql;
    QString log_id;
};

#endif // WITHDRAW_H
