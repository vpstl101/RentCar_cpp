#ifndef SIGHT_EDIT_H
#define SIGHT_EDIT_H
#include "database.h"

#include <QDialog>

namespace Ui {
class sight_edit;
}

class sight_edit : public QDialog
{
    Q_OBJECT

public:
    explicit sight_edit(std::vector<std::string> data, QWidget *parent = nullptr);
    ~sight_edit();

private slots:
    void on_edit_btn_clicked();

private:
    Ui::sight_edit *ui;
    QSqlQuery sql;
    std::string query;
};

#endif // SIGHT_EDIT_H
