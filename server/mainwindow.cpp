#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memberlist.h"
#include "sight.h"
#include "car.h"
#include "reservation.h"
#include "chatting.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(750, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_member_clicked()
{
    this->hide();
    memberlist member;
    member.setModal(true);
    member.exec();
    this->show();
}

void MainWindow::on_sight_clicked()
{
    this->hide();
    sight sight;
    sight.setModal(true);
    sight.exec();
    this->show();

}

void MainWindow::on_rentacar_clicked()
{
    this->hide();
    car car;
    car.setModal(true);
    car.exec();
    this->show();
}

void MainWindow::on_reservation_clicked()
{
    this->hide();
    reservation res;
    res.setModal(true);
    res.exec();
    this->show();
}

