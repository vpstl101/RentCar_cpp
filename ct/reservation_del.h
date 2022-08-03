#ifndef RESERVATION_DEL_H
#define RESERVATION_DEL_H

#include <QDialog>

namespace Ui {
class reservation_del;
}

class reservation_del : public QDialog
{
    Q_OBJECT

public:
    explicit reservation_del(QWidget *parent = nullptr);
    ~reservation_del();

private:
    Ui::reservation_del *ui;
};

#endif // RESERVATION_DEL_H
