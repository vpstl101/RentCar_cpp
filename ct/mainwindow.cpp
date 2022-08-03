#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace  std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked() //로그인 화면
{
    query="SELECT id,pw,grade FROM member WHERE id ='"+ui->getID->text().toStdString()+"'";
    sql.exec(QString::fromStdString(query));
    sql.first();
    if(sql.size() != 0)
    {
        if(sql.value(0).toString()==ui->getID->text() and sql.value(1).toString() == ui->getPW->text())
         {
            QMessageBox::information(this, "Login", "로그인 성공했습니다");
            this->hide();

            log_id = ui->getID->text(); //로그인 아이디

            menu menu(log_id);
            menu.setModal(true);
            menu.exec();
            //this->show();
         }
        else
            QMessageBox::warning(this, "error", "ID 또는 PW 확인하세요");
    }
    else
        QMessageBox::warning(this, "error", "ID 또는 PW 확인하세요");
}


void MainWindow::on_join_clicked() //회원가입 버튼
{
    join signup;
    signup.setModal(true);
    signup.exec();
}
