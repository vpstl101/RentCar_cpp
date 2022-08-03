#include "memberlist.h"
#include "ui_memberlist.h"
#include <QMessageBox>
#include <QDebug>
#include "member_edit.h"
#include "member_add.h"
memberlist::memberlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberlist)
{
    ui->setupUi(this);
    grade = "common";
    list(grade);
}

memberlist::~memberlist()
{
    delete ui;
}


void memberlist::list(std::string type)
{
    ui->commonlist->clear();
    query = "SELECT num, id, pw, name, grade, point, coupon FROM member where grade ='" + type +"'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int id = record.indexOf("id");
    int pw = record.indexOf("pw");
    int name = record.indexOf("name");
    int rating = record.indexOf("grade");
    int point = record.indexOf("point");
    int coupon = record.indexOf("coupon");
    ui->commonlist->setRowCount(sql.size());
    ui->commonlist->setColumnCount(record.count());
    ui->commonlist->setHorizontalHeaderItem(0, new QTableWidgetItem("회원번호"));
    ui->commonlist->setHorizontalHeaderItem(1, new QTableWidgetItem("아이디"));
    ui->commonlist->setHorizontalHeaderItem(2, new QTableWidgetItem("비밀번호"));
    ui->commonlist->setHorizontalHeaderItem(3, new QTableWidgetItem("닉네임"));
    ui->commonlist->setHorizontalHeaderItem(4, new QTableWidgetItem("등급"));
    ui->commonlist->setHorizontalHeaderItem(5, new QTableWidgetItem("포인트"));
    ui->commonlist->setHorizontalHeaderItem(6, new QTableWidgetItem("쿠폰"));
    ui->commonlist->horizontalHeader()->setStretchLastSection(true);
    int i =0;
    while(sql.next())
    {
        ui->commonlist->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->commonlist->setItem(i, 1, new QTableWidgetItem(sql.value(id).toString()));
        ui->commonlist->setItem(i, 2, new QTableWidgetItem(sql.value(pw).toString()));
        ui->commonlist->setItem(i, 3, new QTableWidgetItem(sql.value(name).toString()));
        ui->commonlist->setItem(i, 4, new QTableWidgetItem(sql.value(rating).toString()));
        ui->commonlist->setItem(i, 5, new QTableWidgetItem(sql.value(point).toString()));
        ui->commonlist->setItem(i++, 6, new QTableWidgetItem(sql.value(coupon).toString()));
    }
}


void memberlist::on_edit_btn_clicked()
{
    if(ui->commonlist->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row;
        std::vector<std::string>data;

        row = ui->commonlist->currentRow();
        data.push_back(ui->commonlist->takeItem(row, 1)->text().toStdString());
        data.push_back(ui->commonlist->takeItem(row, 2)->text().toStdString());
        data.push_back(ui->commonlist->takeItem(row, 3)->text().toStdString());
        data.push_back(ui->commonlist->takeItem(row, 4)->text().toStdString());
        data.push_back(ui->commonlist->takeItem(row, 5)->text().toStdString());
        data.push_back(ui->commonlist->takeItem(row, 6)->text().toStdString());

        member_edit edit(data);
        edit.setModal(true);
        edit.exec();
        list(grade);
    }
}

void memberlist::on_delete_btn_clicked()
{
    if(ui->commonlist->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row = ui->commonlist->currentRow();
        query = "DELETE FROM member WHERE id = '" + ui->commonlist->takeItem(row, 1)->text().toStdString() + "'";
        qDebug() << QString::fromStdString(query);
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "", "삭제완료");
        list(grade);
    }
}



void memberlist::on_common_btn_clicked()
{
    grade = "common";
    list(grade);
}

void memberlist::on_premium_btn_clicked()
{
    grade = "premium";
    list(grade);
}

void memberlist::on_vip_btn_clicked()
{
    grade = "vip";
    list(grade);
}



void memberlist::on_new_btn_clicked()
{
    member_add add;
    add.setModal(true);
    add.exec();
    list(grade);
}
