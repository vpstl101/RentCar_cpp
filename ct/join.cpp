#include "mainwindow.h"
#include "menu.h"
#include "join.h"
#include "ui_join.h"
using namespace  std;


join::join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::join)
{
    ui->setupUi(this);
    grade = "common";
}

join::~join()
{    delete ui;}

void join::on_c_click_clicked()
{    grade = "common";}

void join::on_p_click_clicked()
{    grade = "premium";}

void join::on_v_click_clicked()
{    grade ="vip";}

void join::on_newjoin_clicked() //회원가입
{
    QString id = ui->getID->text();
    QString pw = ui->getPW->text();
    QString name = ui->getNAME->text();

    query = "INSERT INTO member (id, pw, name, grade)" "VALUES ('"+id.toStdString()+"', '"+pw.toStdString()+"', '"+name.toStdString()+"', '"+grade+"')";

    sql.exec(QString::fromStdString(query));
    QMessageBox::information(this, "", "회원가입 완료");
    this->close();

}

