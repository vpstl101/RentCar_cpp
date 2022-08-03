#include "member_add.h"
#include "ui_member_add.h"
#include <QMessageBox>
#include <QDebug>
member_add::member_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::member_add)
{
    ui->setupUi(this);
    grade = "common";
    ui->pw_txt->setEnabled(false);
    ui->name_txt->setEnabled(false);
    ui->point_txt->setEnabled(false);
    ui->coupon_txt->setEnabled(false);
}

member_add::~member_add()
{
    delete ui;
}

void member_add::on_add_btn_clicked()
{
    query = "INSERT INTO member (id, pw, name, grade, point, coupon) VAlUES ('"+ ui->id_txt->text().toStdString() +"', '" + ui->pw_txt->text().toStdString()
            + "', '" + ui->name_txt->text().toStdString() + "', '" + grade +"', '" + ui->point_txt->text().toStdString() + "', '" + ui->coupon_txt->text().toStdString() +"')";

    sql.exec(QString::fromStdString(query));
    qDebug()<<QString::fromStdString(query);
    QMessageBox::information(this, "", "등록완료");
    this->close();
}

void member_add::on_common_btn_clicked()
{
    grade = "common";
}

void member_add::on_premium_btn_clicked()
{
    grade = "premium";
}

void member_add::on_vip_btn_clicked()
{
    grade = "vip";
}

void member_add::on_pushButton_clicked()
{
    query = "SELECT id FROM member WHERE id = '" + ui->id_txt->text().toStdString() +"'";
    sql.exec(QString::fromStdString(query));
    if(sql.size() == 0)
    {
        QMessageBox::information(this, "", "사용 가능");
        ui->pw_txt->setEnabled(true);
        ui->name_txt->setEnabled(true);
        ui->point_txt->setEnabled(true);
        ui->coupon_txt->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "error", "사용 불가");
    }
}
