#ifndef SIGHT_H
#define SIGHT_H

#include "database.h"
#include <QDialog>
#include "sight_edit.h"
#include "sight_add.h"

namespace Ui {
class sight;
}

class sight : public QDialog
{
    Q_OBJECT

public:
    explicit sight(QWidget *parent = nullptr);
    ~sight();
    void list();
private slots:
    void on_edit_btn_clicked();

    void on_delete_btn_clicked();

    void on_add_btn_clicked();

private:
    Ui::sight *ui;
    std::string query;
    QSqlQuery sql;
    QSqlRecord record;
};

#endif // SIGHT_H
