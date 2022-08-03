#ifndef SIGHT_ADD_H
#define SIGHT_ADD_H

#include <QDialog>
#include "database.h"

namespace Ui {
class sight_add;
}

class sight_add : public QDialog
{
    Q_OBJECT

public:
    explicit sight_add(QWidget *parent = nullptr);
    ~sight_add();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sight_add *ui;
    std::string query;
    QSqlQuery sql;
};

#endif // SIGHT_ADD_H
