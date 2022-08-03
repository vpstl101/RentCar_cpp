#ifndef CAR_H
#define CAR_H

#include <QDialog>
#include "database.h"

namespace Ui {
class car;
}

class car : public QDialog
{
    Q_OBJECT

public:
    explicit car(QWidget *parent = nullptr);
    ~car();
    void list();

private slots:
    void on_add_btn_clicked();

    void on_edit_btn_clicked();

    void on_delete_btn_clicked();

    void on_comboBox_currentIndexChanged(int index);
private:
    Ui::car *ui;
    QSqlQuery sql;
    QSqlRecord record;
    std::string query;

};

#endif // CAR_H
