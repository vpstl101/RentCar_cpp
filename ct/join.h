#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include "database.h"
using namespace  std;

namespace Ui {
class join;
}

class join : public QDialog
{
    Q_OBJECT

public:
    explicit join(QWidget *parent = nullptr);
    ~join();

private slots:
    void on_newjoin_clicked();
    void on_c_click_clicked();
    void on_p_click_clicked();
    void on_v_click_clicked();

private:
    Ui::join *ui;
    QSqlQuery sql;
    string query;
    string grade;
};

#endif // JOIN_H
