#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_member_clicked();

    void on_sight_clicked();

    void on_rentacar_clicked();

    void on_reservation_clicked();

private:
    Ui::MainWindow *ui;

    Database DB;
    QSqlQuery sql;
    QSqlRecord record;
    std::string query;
};
#endif // MAINWINDOW_H
