#include "myinfo.h"
#include "ui_myinfo.h"
#include <QDebug>

myinfo::myinfo(QString log_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myinfo)
{
    ui->setupUi(this);
    choose="";
    logid=log_id;
    qDebug() << logid;
    list();
}

myinfo::~myinfo()
{
    delete ui;
    QSqlRecord record;
}
void myinfo::on_radioButton_clicked() //pw 버튼
{    choose="pw";}

void myinfo::on_radioButton_2_clicked() //name 버튼
{    choose="name";}

void myinfo::list()
{
    ui->info->clear();

    query="SELECT * FROM member where id='" + logid.toStdString() + "'";

    qDebug() << QString::fromStdString(query);
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int id = record.indexOf("id");
    int pw = record.indexOf("pw");
    int name = record.indexOf("name");
    int grade = record.indexOf("grade");
    int point = record.indexOf("point");
    int coupon = record.indexOf("coupon");
    ui->info->setRowCount(sql.size());
    ui->info->setColumnCount(record.count()-1);
    ui->info->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->info->setHorizontalHeaderItem(1, new QTableWidgetItem("PW"));
    ui->info->setHorizontalHeaderItem(2, new QTableWidgetItem("Name"));
    ui->info->setHorizontalHeaderItem(3, new QTableWidgetItem("Grade"));
    ui->info->setHorizontalHeaderItem(4, new QTableWidgetItem("Point"));
    ui->info->setHorizontalHeaderItem(5, new QTableWidgetItem("Coupon"));

    //rec=quemyinfo.exec();ry.record();
    int i=0;
    while(sql.next())
    {
        ui->info->setItem(i,0,new QTableWidgetItem(sql.value(id).toString()));
        ui->info->setItem(i,1,new QTableWidgetItem(sql.value(pw).toString()));
        ui->info->setItem(i,2,new QTableWidgetItem(sql.value(name).toString()));
        ui->info->setItem(i,3,new QTableWidgetItem(sql.value(grade).toString()));
        ui->info->setItem(i,4,new QTableWidgetItem(sql.value(point).toString()));
        ui->info->setItem(i++,5,new QTableWidgetItem(sql.value(coupon).toString()));
    }
}


void myinfo::on_out_clicked() //탈퇴 버튼 -> 탈퇴 창 이동
{
    withdraw out(logid);
    out.setModal(true);
    out.exec();
}

void myinfo::on_modify_clicked() //수정 버튼
{
    string change = ui->get_mod->text().toStdString();

    query = "UPDATE member SET "+choose+" ='"+change+"' WHERE id='"+logid.toStdString() +"'";

    qDebug() << QString::fromStdString(query); //쿼리문  내용 표시
    sql.exec(QString::fromStdString(query));

    QMessageBox::information(this, "", "수정완료");
    list();
    //this->close();
}

void myinfo::on_back_clicked()
{    this->close();}
