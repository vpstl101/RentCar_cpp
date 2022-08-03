#include "member_edit.h"
#include "ui_member_edit.h"
#include <QMessageBox>
#include <QDebug>

member_edit::member_edit(std::vector<std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::member_edit)
{
    ui->setupUi(this);
    ui->id_txt->setText(QString::fromStdString(data[0]));
    ui->pw_txt->setText(QString::fromStdString(data[1]));
    ui->name_txt->setText(QString::fromStdString(data[2]));
    ui->point_txt->setText(QString::fromStdString(data[4]));
    ui->coupon_txt->setText(QString::fromStdString(data[5]));
    grade = data[3];
    if(grade == "common")
        ui->common_btn->setChecked(true);
    else if(grade == "premium")
        ui->premium_btn->setChecked(true);
    else
        ui->vip_btn->setChecked(true);

}

member_edit::~member_edit()
{
    delete ui;
}

void member_edit::on_edit_btn_clicked()
{
    query = "UPDATE member SET pw = '" + ui->pw_txt->text().toStdString() + "', name = '"
            + ui->name_txt->text().toStdString() + "', grade ='" + grade +"', point ='" +ui->point_txt->text().toStdString()
            + "', coupon = '" + ui->coupon_txt->text().toStdString() + "' where id = '" + ui->id_txt->text().toStdString() +"'";
    qDebug()<<QString::fromStdString(query);
    sql.exec(QString::fromStdString(query));
    QMessageBox::information(this, "", "수정완료");
    this->close();
}

void member_edit::on_common_btn_clicked()
{
    grade = "common";
}

void member_edit::on_premium_btn_clicked()
{
    grade = "premium";
}

void member_edit::on_vip_btn_clicked()
{
    grade = "vip";
}
